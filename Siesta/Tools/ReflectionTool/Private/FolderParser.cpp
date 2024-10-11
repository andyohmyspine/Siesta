#include "FolderParser.h"
#include "Object.h"

#include <fstream>
#include <format>
#include <array>

TFolderParser::TFolderParser(const TPath& FolderPath)
	: m_FolderPath(FolderPath)
{
}

DParsedFolderData TFolderParser::GenerateFolderInfo()
{

	// Go recursively over every file in project
	for (const auto& Entry : TRecursiveDirectoryIterator(m_FolderPath))
	{
		const TPath& FilePath = Entry.path();
		if (FilePath.extension() != ".h")
		{
			continue;
		}

		// Found a header file

		// 1. Read file to buffer
		std::ifstream File(FilePath);
		TStringStream FileSS;
		FileSS << File.rdbuf();
		TString FileContents = FileSS.str();

		// 2. Scan file for classes and structs
		PVector<DFileWord> Words = SplitFileIntoWords(FileContents);
		PVector<DToken> Tokens = TokenizeFile(FilePath.stem().string(), Words);
		m_OutData = ParseTokens(Tokens);
	}

	m_OutData.FolderPath = m_FolderPath.string();
	return m_OutData;
}

PVector<DFileWord> TFolderParser::SplitFileIntoWords(const TString& FileContents)
{
	TString Token;
	PVector<DFileWord> Words;

	// A way to skip comments
	bool OneLineCommentStarted = false;
	bool MultiLineCommentStarted = false;
	int32 LineNumber = 1;

	for (size_t Index = 0; Index < FileContents.size(); ++Index)
	{
#define ADVANCE Index++; if(FileContents.size() > Index) Char = FileContents[Index]; else break
#define PEEK ((FileContents.size() > (Index + 1)) ? (char)FileContents[Index + 1] : (char)-1)
#define FLUSH_TOKEN if(!Token.empty()) { Words.push_back({Token, LineNumber}); Token.clear(); }

		char Char = FileContents[Index];

		if (isspace(Char))
		{
			auto _isnewline = [&] { return Char == '\n' || (Char == '\r' && PEEK == '\n'); };


			if (_isnewline())
			{
				OneLineCommentStarted = false;
			}

			if (!OneLineCommentStarted && !MultiLineCommentStarted)
			{
				if (!Token.empty())
				{
					FLUSH_TOKEN;
				}
			}

			if (_isnewline())
			{
				LineNumber++;
			}

			continue;
		}

		/**
		 * Detect comments
		 */
		if (Char == '/')
		{
			if (PEEK == '/')
				OneLineCommentStarted = true;

			if (PEEK == '*')
				MultiLineCommentStarted = true;

			if (OneLineCommentStarted || MultiLineCommentStarted)
			{
				Token.clear();
				ADVANCE;
				continue;
			}
		}

		/**
		 * Detect multiline comment end
		 */
		if (Char == '*' && PEEK == '/')
		{
			MultiLineCommentStarted = false;
			Token.clear();
			ADVANCE;
			continue;
		}


		/**
		 * Detect special symbols
		 */
		if (!MultiLineCommentStarted && !OneLineCommentStarted)
		{
			if (
				Char == '(' ||
				Char == ')' ||
				Char == ':' ||
				Char == '=' ||
				Char == '{' ||
				Char == '}' ||
				Char == '[' ||
				Char == ']' ||
				Char == ',' ||
				Char == '.' ||
				Char == '*' ||
				Char == '&' ||
				Char == '<' ||
				Char == '>' ||
				Char == ';')
			{
				FLUSH_TOKEN;
				Words.push_back({ std::format("{}", Char), LineNumber });
				continue;
			}
		}

		Token += Char;
	}

	return Words;
}

PVector<DToken> TFolderParser::TokenizeFile(const TString& FileName, const PVector<DFileWord>& Words)
{
	static const PHashMap<TString, ETokenType> SpecialSymbolTokens
	{
		{ SIESTA_STRINGIFY(expose_object), ETokenType::ExposedObjectType },
		{ SIESTA_STRINGIFY(generated_code), ETokenType::GeneratedCode},
		{ SIESTA_STRINGIFY(expose_field), ETokenType::ExposedField },
		{ SIESTA_STRINGIFY(expose_method), ETokenType::ExposeMethod },
		{ "(",ETokenType::LeftParen },
		{ ")",ETokenType::RightParen },
		{ ":",ETokenType::Colon },
		{ "=",ETokenType::Equal },
		{ "{",ETokenType::LeftBrace },
		{ "}",ETokenType::RightBrace },
		{ "[",ETokenType::LeftBracket },
		{ "]",ETokenType::RightBracket },
		{ ",",ETokenType::Comma },
		{ ".",ETokenType::Period },
		{ "*",ETokenType::Star },
		{ "&",ETokenType::Ampersand },
		{ "<",ETokenType::LeftAngular },
		{ ">",ETokenType::RightAngular },
		{ ";", ETokenType::Semicolon},
		{ "class", ETokenType::ClassKeyword },
		{ "struct", ETokenType::StructKeyword },
		{ "public", ETokenType::PublicKeyword },
		{ "private", ETokenType::PrivateKeyword },
		{ "protected", ETokenType::ProtectedKeyword },
		{ "friend", ETokenType::FriendKeyword },

	};

	PVector<DToken> OutTokens;
	int32 LineIndex = 0;
	int32 LastPreprocessorLineIndex = 0;
	bool BeganPreprocessor = false;

	for (uint64 Index = 0; Index < Words.size(); ++Index)
	{
		DFileWord Word = Words[Index];
		LineIndex = Word.LineIndex;

		// Skip all preprocessor directives
		{
			if (Word.Word.starts_with("#"))
			{
				BeganPreprocessor = true;
				LastPreprocessorLineIndex = Word.LineIndex;
				continue;
			}

			if (BeganPreprocessor && (LastPreprocessorLineIndex == Word.LineIndex))
			{
				continue;
			}
			else
			{
				BeganPreprocessor = false;
			}
		}

		if (SpecialSymbolTokens.contains(Word.Word))
		{
			OutTokens.push_back(DToken(SpecialSymbolTokens.at(Word.Word), FileName, Word));
			continue;
		}
		else
		{
			OutTokens.push_back(DToken(ETokenType::Identifier, FileName, Word));
		}
	}

	return OutTokens;
}

DParsedFolderData TFolderParser::ParseTokens(const PVector<DToken>& Tokens)
{
	if (Tokens.empty())
		return {};

	DParsedFolderData OutData;

	int32 BraceDepth = 0;
	static constexpr int32 CLASS_SCOPE_BRACE_DEPTH = 1;

	// Find expose_class
	auto Iter = Tokens.begin();
	using TIterType = decltype(Iter);
	while (Iter != Tokens.end())
	{
		auto _is_end = [&] { return Iter == Tokens.end(); };
		auto _advance = [&] { ++Iter; return !_is_end(); };
		auto _advance_safe = [&]<typename... Args>(fmt::format_string<Args...> Format = "Unexpected end of file", Args&&... InArgs)
		{
			if (!_advance())
				Debug::Critical(Format, std::forward<Args>(InArgs)...);
		};

		auto _peek = [&](TIterType& OutIter) { OutIter = Iter + 1; return OutIter != Tokens.end(); };

		while (Iter->Type != ETokenType::ExposedObjectType)
		{
			if (!_advance())
			{
				goto ending;
			}
		}
#pragma region CLASS METADATA
		// Began class metadata
		{
			_advance_safe("Unexpected end of file while parsing class metadata.");

			DParsedTypeInfo TypeInfo = {};
			if (Iter->Type == ETokenType::LeftParen)
			{
				if (!_advance())
				{
					_advance_safe("Unexpected end of file while parsing class metadata.");
				}

				while (Iter->Type != ETokenType::RightParen)
				{
					if (Iter->Type == ETokenType::Identifier)
					{
						TypeInfo.MetaSpecifiers.push_back(Iter->Name);
						_advance_safe("Unexpected end of file while parsing class metadata.");
					}
					else if (Iter->Type == ETokenType::Comma)
					{
						_advance_safe("Unexpected end of file while parsing class metadata.");
					}
				}
			}
#pragma endregion

#pragma region CLASS NAME, API AND PARENT
			{
				_advance_safe("Unexpected end of file while parsing class name.");

				if (Iter->Type == ETokenType::ClassKeyword)
				{
					TypeInfo.TypeSpecifier = EParsedTypeSpecifier::Class;
				}
				else if (Iter->Type == ETokenType::StructKeyword)
				{
					TypeInfo.TypeSpecifier = EParsedTypeSpecifier::Struct;
				}
				else
				{
					Debug::Critical("Unexpected end of file while parsing class name");
				}

				_advance_safe();

				// Parse class name or API
				if (Iter->Type == ETokenType::Identifier)
				{
					// Check if next is also an identifier
					TIterType PeekIter;
					if (!_peek(PeekIter))
					{
						Debug::Critical("Unexpected end of file while parsing class name");
					}

					if (PeekIter->Type == ETokenType::Identifier)
					{
						TypeInfo.API = Iter->Name;
						_advance_safe();
						TypeInfo.Name = Iter->Name;
						_advance_safe();
					}
					else if (PeekIter->Type == ETokenType::Colon)
					{
						TypeInfo.Name = Iter->Name;
						_advance_safe();
					}
				}

				// Parse parent if exists
				if (Iter->Type == ETokenType::Colon)
				{
					_advance_safe();
					if (Iter->Type != ETokenType::PublicKeyword)
					{
						Debug::Critical("A reflected parent class must have 'public' inheritance specifier.");
					}

					_advance_safe("Unexpected end of file while parsing class parent");
					if (Iter->Type == ETokenType::Identifier)
					{
						TypeInfo.Parent = Iter->Name;
					}
					else
					{
						Debug::Critical("Unexpected token '{}' while expecting an identifier of parent class.", Iter->Name);
					}

					_advance_safe();
				}
				
			}
#pragma endregion

#pragma region FIELD AND METHOD REFLECTION
			if (Iter->Type == ETokenType::LeftBrace)
			{
				// We started the class body
				BraceDepth++;

				_advance_safe("Unexpected end of file while parsing class body.");

				if (Iter->Type != ETokenType::GeneratedCode)
				{
					Debug::Critical("Unexpected token '{}' at the start of the class body. Expected " SIESTA_STRINGIFY(generated_code) "()", Iter->Name);
				}
				else
				{
					TypeInfo.GeneratedBodyLine = Iter->Line;
				}

				// Try reading fields
				while (BraceDepth > 0)
				{
					_advance_safe();

					if (Iter->Type == ETokenType::LeftBrace)
					{
						BraceDepth++;
					}
					else if (Iter->Type == ETokenType::RightBrace)
					{
						BraceDepth--;
					}
					else
					{
						if (BraceDepth == CLASS_SCOPE_BRACE_DEPTH)
						{
							if (Iter->Type == ETokenType::ExposedField)
							{
								DParsedVariableInfo FieldInfo = {};
								FieldInfo.MemberOf = TypeInfo.Name;

								// Start parcing the field
								_advance_safe("Unexpected end of file while parsing field metadata.");
								if (Iter->Type == ETokenType::LeftParen)
								{
									if (!_advance())
									{
										_advance_safe("Unexpected end of file while parsing field metadata.");
									}

									while (Iter->Type != ETokenType::RightParen)
									{
										if (Iter->Type == ETokenType::Identifier)
										{
											FieldInfo.MetaSpecifiers.push_back(Iter->Name);
											_advance_safe("Unexpected end of file while parsing field metadata.");
										}
										else if (Iter->Type == ETokenType::Comma)
										{
											_advance_safe("Unexpected end of file while parsing field metadata.");
										}
									}

									// Parse field type and name
									_advance_safe();
									if (Iter->Type == ETokenType::Identifier)
									{	
										// This is the type, but it may be parameterized, so put it temporarily in the field info and parse type paras.
										FieldInfo.Type = Iter->Name;
										_advance_safe();

										// Try parsing type field name
										if (Iter->Type == ETokenType::Identifier)
										{
											FieldInfo.Name = Iter->Name;
											_advance_safe();
										}
										else if (Iter->Type == ETokenType::LeftAngular)
										{
											// Start parsing type parameters then field name
											_advance_safe();
											while (Iter->Type != ETokenType::RightAngular)
											{
												if (Iter->Type == ETokenType::Identifier)
												{
													FieldInfo.TypeParams.push_back(Iter->Name);
													_advance_safe();
												}
												else if (Iter->Type == ETokenType::Comma)
												{
													// Found comma
													_advance_safe();
												}
												else
												{
													Debug::Critical("Unexpected token '{}' [{} : {}] when parsing field type parameters. Note that nested parameterized types are unsupported.", Iter->Name, Iter->File, Iter->Line);
												}
											}

											// Finished parsing type params, now parse the name
											_advance_safe();

											if (Iter->Type == ETokenType::Identifier)
											{
												FieldInfo.Name = Iter->Name;
												_advance_safe();
											}
											else
											{
												Debug::Critical("Unexpected token {}.", Iter->Name);
											}
										}
										else
										{
											Debug::Critical("Identifier not found.");
										}

										if (Iter->Type != ETokenType::Semicolon)
										{
											// Parse the default value
											if (Iter->Type == ETokenType::Equal)
											{
												_advance_safe();

												TStringStream DefaultValueStream;
												while (Iter->Type != ETokenType::Semicolon)
												{
													// We are forgiving here :)
													DefaultValueStream << Iter->Name;
													_advance_safe();
												}

												FieldInfo.DefaultValue = DefaultValueStream.str();
											}
										}
										
										if (Iter->Type == ETokenType::Semicolon)
										{
											TypeInfo.Fields.push_back(std::move(FieldInfo));
										}
									}
								}
							} // EXPOSE FIELD END

							if (Iter->Type == ETokenType::ExposeMethod)
							{
								
							}
						}
					}
				}
			}
#pragma endregion

			// Flush type
			OutData.Types.push_back(std::move(TypeInfo));

			if (!_advance())
			{
				break;
			}
		}

	ending:
		continue;
	}

	return OutData;
}
