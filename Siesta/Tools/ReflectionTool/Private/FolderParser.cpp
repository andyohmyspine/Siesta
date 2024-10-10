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
	static PHashMap<TString, ETokenType> SpecialSymbolTokens
	{
		{ SIESTA_STRINGIFY(expose_class), ETokenType::ExposedClass },
		{ SIESTA_STRINGIFY(expose_code), ETokenType::GeneratedBody},
		{ SIESTA_STRINGIFY(expose_field), ETokenType::ExposedField },
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

template<ETokenType ... Types>
struct DTokenPattern
{
	static constexpr std::array<ETokenType, sizeof...(Types)> Pattern{
		Types...
	};

	template<typename T>
	inline constexpr bool operator==(const T& Other)
	{
		return false;
	}

	template<>
	inline constexpr bool operator==<DTokenPattern>(const DTokenPattern& Other)
	{
		return true;
	}

	inline constexpr ETokenType operator[](size_t Index) const { return Pattern[Index]; }
};

// Main patterns
static constexpr DTokenPattern <
	ETokenType::ExposedClass, // expose_class
	ETokenType::ClassKeyword, // class
	ETokenType::Identifier,   // class name,
	ETokenType::LeftBrace,	  // {
	ETokenType::GeneratedBody // expose_code
> CLASS_WITHOUT_PARENT_NO_API;

static constexpr DTokenPattern <
	ETokenType::ExposedClass, // expose_class
	ETokenType::ClassKeyword, // class
	ETokenType::Identifier,   // class name,
	ETokenType::Identifier,   // API_NAME,
	ETokenType::LeftBrace,	  // {
	ETokenType::GeneratedBody // expose_code
> CLASS_WITHOUT_PARENT_WITH_API;

static constexpr DTokenPattern<
	ETokenType::ExposedClass,
	ETokenType::ClassKeyword,
	ETokenType::Identifier,
	ETokenType::Colon,
	ETokenType::PublicKeyword,
	ETokenType::Identifier,
	ETokenType::LeftBrace,
	ETokenType::GeneratedBody
> CLASS_WITH_PARENT_NO_API;

static constexpr DTokenPattern<
	ETokenType::ExposedClass,
	ETokenType::ClassKeyword,
	ETokenType::Identifier,
	ETokenType::Identifier,
	ETokenType::Colon,
	ETokenType::PublicKeyword,
	ETokenType::Identifier,
	ETokenType::LeftBrace,
	ETokenType::GeneratedBody
> CLASS_WITH_PARENT_WITH_API;

struct DFoundPattern
{
	uint64 StartIndex;
	PVector<DToken> Tokens;
};

template<ETokenType... PatternTypes>
PVector<DFoundPattern> FindPattern(DTokenPattern<PatternTypes...> Pattern, const PVector<DToken>& Tokens)
{
	if (Tokens.empty())
	{
		return {};
	}

	// Find 0th element to be similar
	size_t PatternIndex = 0;
	PVector<DFoundPattern> Output;

	int32 Index = 0;
	while (Index < Tokens.size())
	{
		DFoundPattern CurrentPattern{};

	restart:
		ETokenType Start = Pattern[PatternIndex];
		while (Tokens[Index++].Type != Start)
		{
			// Could not find anything
			if (Tokens.size() <= Index)
				return Output;
		}

		// We found the first element. Now seek for the rest
		CurrentPattern.Tokens.push_back(Tokens[(size_t)Index - 1]);
		CurrentPattern.StartIndex = (uint64)Index - 1;
		while (++PatternIndex < Pattern.Pattern.size())
		{
			auto& Token = Tokens[Index++];
			auto PatternValue = Pattern[PatternIndex];

			if (Token.Type != PatternValue)
			{
				CurrentPattern.Tokens.clear();
				CurrentPattern.StartIndex = 0;
				PatternIndex = 0;
				goto restart;
			}
			else
			{
				CurrentPattern.Tokens.push_back(Tokens[(size_t)Index - 1]);
			}
		}

		Output.push_back(CurrentPattern);
		PatternIndex = 0;
		CurrentPattern = {};
		Index++;
	}

	return Output;
}

DParsedFolderData TFolderParser::ParseTokens(const PVector<DToken>& Tokens)
{
	// Define main patterns

	DParsedFolderData OutData;

	auto WithoutParentWithApi = FindPattern(CLASS_WITHOUT_PARENT_WITH_API, Tokens);
	auto WithParentWithApi = FindPattern(CLASS_WITH_PARENT_WITH_API, Tokens);
	auto WitouthParentWithoutApi = FindPattern(CLASS_WITHOUT_PARENT_NO_API, Tokens);
	auto WithParentWithoutApi = FindPattern(CLASS_WITH_PARENT_NO_API, Tokens);

	return OutData;
}
