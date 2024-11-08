Siesta_CreateSharedModule(ShaderCompiler)

target_link_libraries(ShaderCompiler PUBLIC CoreAll)

if(WIN32)
    target_link_libraries(ShaderCompiler PRIVATE DXC)
    target_compile_definitions(ShaderCompiler PRIVATE SIESTA_SHADER_COMPILER_DXC)
    Siesta_CopyDXCBinaries(ShaderCompiler)
endif()