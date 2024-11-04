Siesta_CreateLoadableModule(Siesta.RenderD3D12)

target_link_libraries(Siesta.RenderD3D12 
    PUBLIC 
        Siesta.RenderCore
        
    PRIVATE
        DirectX-Headers
        DirectX-Guids
        dxgi
        d3d12
        D3D12MemoryAllocator)