if(WIN32 OR UNIX)
    add_subdirectory(Siesta-PlatformGLFW)
    add_subdirectory(Siesta-ShaderCompilerDXC)

    if(SIESTA_USE_D3D12)
        add_subdirectory(Siesta-RenderD3D12)
    endif()
endif()