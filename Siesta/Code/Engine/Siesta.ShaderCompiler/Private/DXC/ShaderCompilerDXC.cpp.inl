#include "ShaderCompilerDXC.h"

#include <comdef.h>

inline void ThrowIfFailed(HRESULT Result)
{
	if (FAILED(Result))
	{
		_com_error Error(Result);
#ifndef UNICODE
		Debug::Critical("HRESULT failed with error message: {}", Error.ErrorMessage());
#else
		char* MessageBuffer = new char[1024];
		wcstombs(MessageBuffer, Error.ErrorMessage(), 1024);
		Debug::Critical("HRESULT failed with error message: {}", MessageBuffer);
#endif
	}
}


SDXCShaderCompiler::SDXCShaderCompiler()
{
	ThrowIfFailed(DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&m_Utils)));
}

DCompiledData SDXCShaderCompiler::CompileShader(const TString& Path, const TString& EntryPoint, ECompilerShaderStage::Type Stage)
{
	return {};
}

void SDXCShaderCompiler::ClearCompiledData(DCompiledData* Data)
{
}
