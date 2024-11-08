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

DCompiledData SDXCShaderCompiler::CompileShader(const SShaderCompilerEnvironmentConfiguration& Env, const TString& Path, const TString& EntryPoint, ECompilerShaderStage::Type Stage)
{
	// Read file from path
	if (Path.empty())
	{
		return {};
	}

	const TString ShaderSource{ SFileHelpers::ReadFileToString(Path) };
	ComPtr<IDxcBlobEncoding> SourceBlob;
	ThrowIfFailed(m_Utils->CreateBlob(ShaderSource.data(), ShaderSource.size(), CP_UTF8, &SourceBlob));

	ComPtr<IDxcCompiler3> Compiler;
	ThrowIfFailed(DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&Compiler)));

	// Convert strings to wide strings
	PDynArray<LPCWSTR> Arguments;

	TWideString WideEntryPoint = StringToWideString(EntryPoint);
	Arguments.push_back(L"-E");
	Arguments.push_back(WideEntryPoint.c_str());

	TWideString TargetProfile = match_enum(Stage)
	{
		match_case(VertexShader) return L"vs_6_6";
		match_case(PixelShader) return L"ps_6_6";
		match_case(ComputeShader) return L"cs_6_6";
	} end_match;
	Arguments.push_back(L"-T");
	Arguments.push_back(TargetProfile.c_str());

#ifdef SIESTA_ENABLE_GPU_VALIDATION
	Arguments.push_back(DXC_ARG_WARNINGS_ARE_ERRORS);
	Arguments.push_back(DXC_ARG_DEBUG);

	Arguments.push_back(L"-Qstrip_debug");
#endif
	Arguments.push_back(L"-QStrip_reflect");

	DxcBuffer SourceBuffer = 
	{
		.Ptr = SourceBlob->GetBufferPointer(),
		.Size = SourceBlob->GetBufferSize(),
		.Encoding = 0,
	};
	ComPtr<IDxcResult> CompileResult;
	ThrowIfFailed(Compiler->Compile(&SourceBuffer, Arguments.data(), (UINT32)Arguments.size(), nullptr, IID_PPV_ARGS(&CompileResult)));

	// Handle errors.
	ComPtr<IDxcBlobUtf8> Errors;
	ThrowIfFailed(CompileResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&Errors), nullptr));
	if (Errors && Errors->GetStringLength() > 0)
	{
		Debug::Critical("Failed to compile shader '{}': {}", Path, (const char*)Errors->GetBufferPointer());
	}
	
	// Get the DXIL out
	ComPtr<IDxcBlob> CompileBinary;
	ThrowIfFailed(CompileResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&CompileBinary), nullptr));

	return {};
}

void SDXCShaderCompiler::ClearCompiledData(DCompiledData* Data)
{
	if (Data->Binary)
	{
		delete[] reinterpret_cast<const uint8*>(Data->Binary);
		Data->Hash = 0;
		Data->Size = 0;

		if (Data->Reflection)
		{
			delete Data->Reflection;
		}
	}
}
