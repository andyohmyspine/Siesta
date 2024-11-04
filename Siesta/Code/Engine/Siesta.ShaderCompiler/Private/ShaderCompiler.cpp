#include "ShaderCompiler.h"

#ifdef SIESTA_SHADER_COMPILER_DXC
	#include "DXC/ShaderCompilerDXC.h"
	#include "DXC/ShaderCompilerDXC.cpp.inl"

IShaderCompiler* CreateShaderCompiler()
{
	return new SDXCShaderCompiler();
}
#endif