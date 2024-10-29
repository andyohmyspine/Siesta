#pragma once

#include "SiestaCore.h"
#include "Type.h"
#include "SiestaFilesystem.h"

enum ETypeDecorators
{
	TD_None = 0,
	TD_Const = 1 << 0,
	TD_Reference = 1 << 1,
	TD_Pointer = 1 << 2,

	TD_ConstReference = TD_Const | TD_Reference,
	TD_ConstPointer = TD_Const | TD_Pointer,
};

struct DParsedVariableInfo
{
	TString Name;
	TString Type;
	uint16 DecoratorMask;
	PDynArray<TString> TypeParams;
	TString DefaultValue;
	TString MemberOf;
	PDynArray<TString> MetaSpecifiers;
};

struct DParsedMethodInfo
{
	TString Name;
	TString ReturnType;
	uint16 ReturnDecoratorMask;
	uint16 MethodDecoratorMask;
	PDynArray<TString> ReturnTypeParams;
	PDynArray<DParsedVariableInfo> Parameters;
	TString DefaultValue;
	TString MemberOf;
	PDynArray<TString> MetaSpecifiers;
};

enum class EParsedTypeSpecifier
{
	Class,
	Struct,
};

struct DParsedTypeInfo
{
	TString Name;
	TString API;
	TString Parent;
	TString File;
	EParsedTypeSpecifier TypeSpecifier;
	int32 GeneratedBodyLine;
	PDynArray<TString> MetaSpecifiers;
	PDynArray<DParsedVariableInfo> Fields;
	PDynArray<DParsedMethodInfo> Methods;
};

struct DParsedFolderData
{
	bool ContainsReflection{};
	TString FolderPath{};
	PDynArray<DParsedTypeInfo> Types{};
};

template<typename T>
struct DProtectedList
{
	PList<T> Data;
	mutable TMutex DataMutex;

	void PushBack(T&& Value)
	{
		TLockGuard guard(DataMutex);
		Data.push_back(std::move(Value));
	}

	void PushBack(const T& Value)
	{
		TLockGuard guard(DataMutex);
		Data.push_back(Value);
	}

	template<typename Func>
	auto FindByPredicate(Func&& Predicate) const
	{
		TLockGuard Lock(DataMutex);
		return std::find_if(begin(), end(), std::forward<Func>(Predicate));
	}

	inline auto begin() const { return Data.begin(); }
	inline auto end() const { return Data.end(); }
};

enum class ETokenType
{
	None,
	ExposedObjectType,
	ExposedField,
	ExposeMethod,
	ConstKeyword,
	
	LeftParen,
	RightParen,
	LeftBrace,
	RightBrace,
	LeftAngular,
	RightAngular,
	LeftBracket,
	RightBracket,
	Comma,
	Period,
	Colon,
	Equal,
	Star,
	Ampersand,
	Semicolon,

	ClassKeyword,
	StructKeyword,
	PublicKeyword,
	PrivateKeyword,
	ProtectedKeyword,
	FriendKeyword,
	Identifier,
	GeneratedCode,
};

struct DFileWord
{
	TString Word;
	int32 LineIndex;
};

struct DToken
{
	DToken() = default;
	DToken(ETokenType InType, const TString& InFile, const DFileWord& Word)
		: Type(InType)
		, Name(Word.Word)
		, File(InFile)
		, Line(Word.LineIndex)
	{
	}

	ETokenType Type {};
	TString Name {};
	TString File {};
	int32 Line {};

	void Reset()
	{
		Type = {};
		Name = {};
		File = {};
		Line = {};
	}

	bool Valid() const { return Type != ETokenType::None; }
};

class SFolderParser
{
public:
	SFolderParser(const TPath& FolderPath);

	DParsedFolderData GenerateFolderInfo();

private:
	PDynArray<DFileWord> SplitFileIntoWords(const TString& FileContents);
	PDynArray<DToken> TokenizeFile(const TString& FileName, const PDynArray<DFileWord>& Words);
	void ParseTokens(const PDynArray<DToken>& Tokens);

private:
	TPath m_FolderPath;
	DParsedFolderData m_OutData{};
};