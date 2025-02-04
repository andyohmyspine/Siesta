#pragma once

#include "Core.h"
#include "CPUBlob.h"
#include "HAL/RenderCore/Interfaces/Shader.h"

struct DShaderReflectionData
{
};

struct DCompiledData
{
	SCPUBlob* Binary;
	DShaderReflectionData* Reflection;
	uint64 Hash;

	inline bool IsValid() const 
	{
		return Binary != nullptr && Binary->GetBufferSize() > 0;
	}
};

class SShaderCompilerEnvironmentConfiguration
{
public:
	void AddCompileArgument(const TString& Argument);
	void AddCompileArgumentWithValue(const TString& Argument, const TString& Value);

	inline const auto& GetCompileArguments() const { return m_CompileArguments; }

private:
	PDynArray<TString> m_CompileArguments;
};

class IShaderCompiler
{
public:
	virtual DCompiledData CompileShader(const SShaderCompilerEnvironmentConfiguration& Env, const TString& Path, const TString& EntryPoint, EShaderStage::Type Stage) = 0;
	virtual void ClearCompiledData(DCompiledData* Data) = 0;
};

extern IShaderCompiler* CreateShaderCompiler();