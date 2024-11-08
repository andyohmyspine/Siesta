Siesta_CreateSharedModule(RenderCore)

target_link_libraries(RenderCore PUBLIC CoreAll)

if(NOT SIESTA_BUILD_DIST)
    target_link_libraries(RenderCore PRIVATE ShaderCompiler)
endif()
