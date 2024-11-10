Siesta_CreateStaticModule(Siesta-Engine)

target_link_libraries(Siesta-Engine PUBLIC Siesta-Core)

if(WIN32 OR UNIX)
    target_link_libraries(Siesta-Engine PUBLIC Siesta-PlatformGLFW)
endif()

if(WIN32)
    target_link_libraries(Siesta-Engine PRIVATE DXC)
    target_compile_definitions(Siesta-Engine PRIVATE SIESTA_SHADER_COMPILER_DXC)
endif()

if(SIESTA_USE_D3D12)
    target_link_libraries(Siesta-Engine    
        PRIVATE
            DirectX-Headers
            DirectX-Guids
            dxgi
            d3d12
            D3D12MemoryAllocator
            Siesta-ShaderCompilerDXC
            Siesta-RenderD3D12)
endif()

macro(Siesta_CopyRequiredBinaries _ModuleName)
    Siesta_CopyDXCBinaries(${_ModuleName})
endmacro()