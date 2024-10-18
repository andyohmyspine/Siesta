add_subdirectory(Siesta.Engine)
add_subdirectory(Siesta.RenderCore)

if(WIN32)
    add_subdirectory(Siesta.RenderD3D12)
endif()