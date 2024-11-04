add_subdirectory(Siesta.Engine)
add_subdirectory(Siesta.RenderCore)
add_subdirectory(Siesta.Renderer)

if(NOT SIESTA_BUILD_DIST)
    add_subdirectory(Siesta.ShaderCompiler)
endif()

if(WIN32)
    add_subdirectory(Siesta.RenderD3D12)
endif()