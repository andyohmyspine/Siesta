Siesta_CreateLoadableModule(Siesta.RenderD3D12)

target_link_libraries(Siesta.RenderD3D12 
    PUBLIC 
        Siesta.RenderCore
        
    PRIVATE
        d3d12
        dxgi)