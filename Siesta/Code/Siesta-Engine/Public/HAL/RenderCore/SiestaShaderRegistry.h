#pragma once

#include "SiestaCore.h"
#include "HAL/RenderCore/Interfaces/SiestaShader.h"

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

	inline SShader** GetForStage(EShaderStage::Type Stage)
	{
		switch (Stage)
		{
			case EShaderStage::VertexShader:
				return &VS;
			case EShaderStage::PixelShader:
				return &PS;
			case EShaderStage::ComputeShader:
				return &CS;
			default:
				Debug::Critical("Unknown shader stage.");
				break;
		}

		Debug::Critical("Unknown shader stage.");
		return nullptr;
	}
};

class SShaderRegistry
{
public:
	static SShaderRegistry& Get();

	SShaderRegistry();

	static SShader* GetShader(const TString& Name, EShaderStage::Type Stage);

	template <typename T>
	static T* GetShader(const TString& Name, EShaderStage::Type Stage)
	{
		return static_cast<T*>(GetShader(Name, Stage));
	}

	static void RegisterShader(const TString& Name, EShaderStage::Type Stage, SShader* Shader);

#ifdef SIESTA_USE_SHADER_COMPILER
	static SShader* CompileShader(const TString& Name, EShaderStage::Type Stage);
#endif

private:
	PHashMap<TString, DShaderBinary> m_Shaders;

#ifdef SIESTA_USE_SHADER_COMPILER
	class IShaderCompiler* m_ShaderCompiler{};
#endif
};
