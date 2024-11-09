#include "HAL/RenderCore/ShaderCompiler.h"

void SShaderCompilerEnvironmentConfiguration::AddCompileArgument(const TString& Argument)
{
	m_CompileArguments.push_back(Argument);
}

void SShaderCompilerEnvironmentConfiguration::AddCompileArgumentWithValue(const TString& Argument, const TString& Value)
{
	m_CompileArguments.push_back(Argument + "=" + Value);
}
