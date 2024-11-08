#pragma once

#include "CoreAll.h"
#include "RenderCoreAPI.h"
#include "Interfaces/SiestaShader.h"

class SShader;

#ifndef SIESTA_BUILD_DIST
	#define SIESTA_USE_SHADER_COMPILER
	#define SIESTA_SHADER_COMPILER_MODULE_NAME "ShaderCompiler"
#endif

struct DShaderBinary
{
	SShader* VS;
	SShader* PS;
	SShader* CS;
};

class RENDERCORE_API SShaderRegistry
{
public:
	static SShaderRegistry& Get();

	SShaderRegistry();

	static SShader* GetShader(const TString& Name, EShaderStage::Type Stage);

	template <typename T>
	static T* GetShader(const TString& Name)
	{
		return static_cast<T*>(GetShader(Name));
	}

	static void RegisterShader(const TString& Name, EShaderStage::Type Stage, SShader* Shader);

#ifdef SIESTA_USE_SHADER_COMPILER
	static SShader* CompileShader(const TString& Path, const TString& EntryPoint, EShaderStage::Type Stage);
#endif

private:
	PHashMap<TString, DShaderBinary> m_Shaders;

#ifdef SIESTA_USE_SHADER_COMPILER
	SModule* m_ShaderCompilerModule {};
	class IShaderCompiler* m_ShaderCompiler{};
#endif
};
