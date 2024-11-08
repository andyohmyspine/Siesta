#pragma once

#include "CoreAll.h"
#include "ShaderCompilerAPI.h"

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

struct DShaderReflectionData
{
};

struct DCompiledData
{
	void* Binary;
	DShaderReflectionData* Reflection;
	uint64 Size;
	uint64 Hash;

	inline bool IsValid() const 
	{
		return Binary != nullptr && Size > 0;
	}
};

class SHADERCOMPILER_API SShaderCompilerEnvironmentConfiguration
{
public:
	void AddCompileArgument(const TString& Argument);
	void AddCompileArgumentWithValue(const TString& Argument, const TString& Value);

	inline const auto& GetCompileArguments() const { return m_CompileArguments; }

private:
	PDynArray<TString> m_CompileArguments;
};

class SHADERCOMPILER_API IShaderCompiler
{
public:
	virtual DCompiledData CompileShader(const SShaderCompilerEnvironmentConfiguration& Env, const TString& Path, const TString& EntryPoint, ECompilerShaderStage::Type Stage) = 0;
	virtual void ClearCompiledData(DCompiledData* Data) = 0;
};

SHADERCOMPILER_API IShaderCompiler* CreateShaderCompiler();