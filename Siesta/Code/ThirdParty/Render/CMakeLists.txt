if(WIN32)
    add_subdirectory(DirectX-Headers)
    add_subdirectory(DXC)
    add_subdirectory(D3D12MemoryAllocator)

    if(MSVC)
        set_target_properties(DirectX-Headers DirectX-Guids D3D12MemoryAllocator PROPERTIES FOLDER Siesta/ThirdParty/Render)
    endif()
endif()