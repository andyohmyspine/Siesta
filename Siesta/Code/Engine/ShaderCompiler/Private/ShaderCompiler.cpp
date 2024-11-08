#include "ShaderCompiler.h"

#ifdef SIESTA_SHADER_COMPILER_DXC
	#include "DXC/ShaderCompilerDXC.h"
	#include "DXC/ShaderCompilerDXC.cpp.inl"

IShaderCompiler* CreateShaderCompiler()
{
	return new SDXCShaderCompiler();
}
#endif

void SShaderCompilerEnvironmentConfiguration::AddCompileArgument(const TString& Argument)
{
	m_CompileArguments.push_back(Argument);
}

void SShaderCompilerEnvironmentConfiguration::AddCompileArgumentWithValue(const TString& Argument, const TString& Value)
{
	m_CompileArguments.push_back(Argument + "=" + Value);
}
