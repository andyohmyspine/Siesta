#include "HAL/RenderCore/ShaderRegistry.h"
#include "HAL/RenderCore/ShaderCompiler.h"

SShaderRegistry& SShaderRegistry::Get()
{
	static SShaderRegistry Instance;
	return Instance;
}

SShaderRegistry::SShaderRegistry()
#ifdef SIESTA_USE_SHADER_COMPILER
	: m_ShaderCompiler(CreateShaderCompiler())
#endif
{
}

static TString GetEntryPointName(EShaderStage::Type Stage)
{
	return match_enum(Stage)
	{
		match_case(VertexShader) return TString("MainVS");
		match_case(PixelShader) return TString("MainPS");
		match_case(ComputeShader) return TString("MainCS");
	}
	end_match;
}

SShader* SShaderRegistry::GetShader(const TString& Name, EShaderStage::Type Stage)
{
	// If we have no shader entry or the shader for this stage is null, compile it or throw an error
	if (!Get().m_Shaders.contains(Name) || *Get().m_Shaders.at(Name).GetForStage(Stage) == nullptr)
	{
#ifdef SIESTA_USE_SHADER_COMPILER
		*Get().m_Shaders[Name].GetForStage(Stage) = CompileShader(Name, Stage);
#else
		Debug::Critical("Could not find shader binary for shader '{}'.");
#endif
	}

	return match_enum(Stage)
	{
		match_case(VertexShader) return Get().m_Shaders.at(Name).VS;
		match_case(PixelShader) return Get().m_Shaders.at(Name).PS;
		match_case(ComputeShader) return Get().m_Shaders.at(Name).CS;
	}
	end_match;
}

void SShaderRegistry::RegisterShader(const TString& Name, EShaderStage::Type Stage, SShader* Shader)
{
	switch (Stage)
	{
		case EShaderStage::VertexShader:
			Get().m_Shaders[Name].VS = Shader;
			break;
		case EShaderStage::PixelShader:
			Get().m_Shaders[Name].PS = Shader;
			break;
		case EShaderStage::ComputeShader:
			Get().m_Shaders[Name].CS = Shader;
			break;
		default:
			Debug::Critical("Unknown shader type");
	}
}

#ifdef SIESTA_USE_SHADER_COMPILER
	#include "HAL/RenderCore/ShaderCompiler.h"

SShader* SShaderRegistry::CompileShader(const TString& Name, EShaderStage::Type Stage)
{
	const TString ShaderPath = SHADER_PATH(Name);
	const TString EntryPoint = GetEntryPointName(Stage);
	Debug::Trace("Compiling shader '{}' ['{}']", Name, EntryPoint);

	auto& This = Get();
	SShader* OutShader = new SShader(Name, EntryPoint, Stage);

	SShaderCompilerEnvironmentConfiguration Env;
	DCompiledData CompiledData = This.m_ShaderCompiler->CompileShader(Env, ShaderPath, EntryPoint, Stage);
	{
		PUniquePtr<SCPUBlob> Blob = WrapUnique(CompiledData.Binary);
		Blob->AddRef();

		Detail::SetShaderByteCode(OutShader, std::move(Blob));
		RegisterShader(Name, Stage, OutShader);
	}
	This.m_ShaderCompiler->ClearCompiledData(&CompiledData);
	return OutShader;
}
#endif
