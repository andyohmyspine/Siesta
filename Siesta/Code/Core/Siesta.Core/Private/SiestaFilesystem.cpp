#include "SiestaFilesystem.h"

SPaths SPaths::Instance;

SPaths::SPaths()
{
	m_RootPath = TString(SIESTA_ROOT_DIR) + '/';
	m_EngineRootPath = m_RootPath + "/Siesta/";
	m_EngineShadersPath = m_EngineRootPath + "/Shaders/";
}

TStringView SPaths::GetRootPath()
{
	return Instance.m_RootPath;
}

TStringView SPaths::GetEngineRootPath()
{
	return Instance.m_EngineRootPath;
}

TStringView SPaths::GetEngineShadersPath()
{
	return Instance.m_EngineShadersPath;
}

TString SPaths::MakeShaderPath(TStringView Path)
{
	return TString(Instance.GetEngineShadersPath()) + '/' + TString(Path);
}
