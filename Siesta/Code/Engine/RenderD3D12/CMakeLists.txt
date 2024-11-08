Siesta_CreateLoadableModule(RenderD3D12)

target_link_libraries(RenderD3D12 
    PUBLIC 
        RenderCore
        
    PRIVATE
        DirectX-Headers
        DirectX-Guids
        dxgi
        d3d12
        D3D12MemoryAllocator)