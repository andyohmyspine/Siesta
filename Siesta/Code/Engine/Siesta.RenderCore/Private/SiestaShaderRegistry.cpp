#include "SiestaShaderRegistry.h"

SShaderRegistry& SShaderRegistry::Get()
{
	static SShaderRegistry Instance;
	return Instance;
}

SShaderRegistry::SShaderRegistry()
#ifdef SIESTA_USE_SHADER_COMPILER
	: m_ShaderCompilerModule(SModuleManager::GetOrLoad(SIESTA_SHADER_COMPILER_MODULE_NAME))
	, m_ShaderCompiler(CreateShaderCompiler())
#endif
{
}

SShader* SShaderRegistry::GetShader(const TString& Name, EShaderStage::Type Stage)
{
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
	#include "ShaderCompiler.h"

SShader* SShaderRegistry::CompileShader(const TString& Path, const TString& EntryPoint, EShaderStage::Type Stage)
{
	Debug::Trace("Compiling shader '{}' ['{}']", Path, EntryPoint);

	auto& This = Get();
	SShader* OutShader = new SShader(Path, EntryPoint, Stage);
	DCompiledData CompiledData = This.m_ShaderCompiler->CompileShader(Path, EntryPoint, (ECompilerShaderStage::Type)Stage);
	{
		PUniquePtr<SCPUBlob> Blob = WrapUnique(AllocateCPUBlob(CompiledData.Size, CompiledData.Binary));
		Detail::SetShaderByteCode(OutShader, std::move(Blob));
		RegisterShader(Path, Stage, OutShader);
	}
	This.m_ShaderCompiler->ClearCompiledData(&CompiledData);
	return OutShader;
}
#endif
