add_subdirectory(Siesta.Engine)
add_subdirectory(Siesta.RenderCore)
add_subdirectory(Siesta.Renderer)

if(WIN32)
    add_subdirectory(Siesta.RenderD3D12)
endif()