#pragma once

#include "Siesta.CoreAPI.h"
#include <filesystem>
#include "SiestaTypes.h"

using TPath = std::filesystem::path;
using TRecursiveDirectoryIterator = std::filesystem::recursive_directory_iterator;

class SIESTA_CORE_API SPaths
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