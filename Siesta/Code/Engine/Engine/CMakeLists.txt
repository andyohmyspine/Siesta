Siesta_CreateSharedModule(Engine)

target_link_libraries(Engine 
PUBLIC 
	CoreAll

PRIVATE
	Renderer
)

if(WIN32)
	add_dependencies(Engine RenderD3D12)
endif()