add_subdirectory(Engine)
add_subdirectory(RenderCore)
add_subdirectory(Renderer)

if(NOT SIESTA_BUILD_DIST)
    add_subdirectory(ShaderCompiler)
endif()

if(WIN32)
    add_subdirectory(RenderD3D12)
endif()