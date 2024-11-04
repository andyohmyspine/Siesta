Siesta_CreateSharedModule(Siesta.RenderCore)

target_link_libraries(Siesta.RenderCore PUBLIC Siesta.CoreAll)

if(NOT SIESTA_BUILD_DIST)
    target_link_libraries(Siesta.RenderCore PRIVATE Siesta.ShaderCompiler)
endif()