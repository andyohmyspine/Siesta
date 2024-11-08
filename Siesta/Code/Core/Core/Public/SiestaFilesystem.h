#pragma once

#include "CoreAPI.h"
#include <filesystem>
#include "SiestaTypes.h"

using TPath = std::filesystem::path;
using TRecursiveDirectoryIterator = std::filesystem::recursive_directory_iterator;

class CORE_API SPaths
{
	static SPaths Instance;

public:
	SPaths();

	static TStringView GetRootPath();
	static TStringView GetEngineRootPath();
	static TStringView GetEngineShadersPath();

	static TString MakeShaderPath(TStringView Path);

private:
	TString m_RootPath;
	TString m_EngineRootPath;
	TString m_EngineShadersPath;
};

class CORE_API SFileHelpers
{
public:
	static TString ReadFileToString(const TString& Path);
};