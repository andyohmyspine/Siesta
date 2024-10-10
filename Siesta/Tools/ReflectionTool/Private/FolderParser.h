#pragma once

#include "SiestaCore.h"
#include "Type.h"
#include "SiestaFilesystem.h"

struct DParsedTypeInfo
{
	TString Name;
	TString API;
	TString Parent;
};

struct DParsedFolderData
{
	bool ContainsReflection{};
	TString FolderPath{};
	PVector<DParsedTypeInfo> Types{};
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

class TFolderParser
{
public:
	TFolderParser(const TPath& FolderPath);

	DParsedFolderData GenerateFolderInfo();

private:
	void ReadFileTypes(const TString& FileContents);

private:
	TPath m_FolderPath;
	DParsedFolderData m_OutData{};
};