Siesta_CreateSharedModule(Siesta.Engine)

target_link_libraries(Siesta.Engine 
PUBLIC 
	Siesta.CoreAll

PRIVATE
	Siesta.Renderer
)

if(WIN32)
	add_dependencies(Siesta.Engine Siesta.RenderD3D12)
endif()