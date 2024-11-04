Siesta_CreateSharedModule(Siesta.ShaderCompiler)

target_link_libraries(Siesta.ShaderCompiler PUBLIC Siesta.CoreAll)

if(WIN32)
    target_link_libraries(Siesta.ShaderCompiler PRIVATE DXC)
    target_compile_definitions(Siesta.ShaderCompiler PRIVATE SIESTA_SHADER_COMPILER_DXC)
    Siesta_CopyDXCBinaries(Siesta.ShaderCompiler)
endif()