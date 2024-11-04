#pragma once

#include "CoreAll.h"
#include "Siesta.ShaderCompilerAPI.h"

namespace ECompilerShaderStage
{
	enum Type : uint8
	{
		None = 0,
		VertexShader = 1 << 0,
		PixelShader = 1 << 1,
		ComputeShader = 1 << 2,
	};
	using Mask = uint8;
} // namespace EShaderStage

struct DCompiledData
{
	void* Binary;
	uint64 Size;
};

class SIESTA_SHADERCOMPILER_API IShaderCompiler
{
public:
	virtual DCompiledData CompileShader(const TString& Path, const TString& EntryPoint, ECompilerShaderStage::Type Stage) = 0;
	virtual void ClearCompiledData(DCompiledData* Data) = 0;
};

SIESTA_SHADERCOMPILER_API IShaderCompiler* CreateShaderCompiler();