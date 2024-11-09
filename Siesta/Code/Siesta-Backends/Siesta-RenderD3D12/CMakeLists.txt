Siesta_CreateStaticModule(Siesta-RenderD3D12)

target_link_libraries(Siesta-RenderD3D12 PUBLIC
    Siesta-Engine
    DirectX-Headers
    DirectX-Guids

    d3d12
    dxgi
    DXC
    D3D12MemoryAllocator
)