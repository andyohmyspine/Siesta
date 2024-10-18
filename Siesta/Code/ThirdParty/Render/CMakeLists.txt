if(WIN32)
    add_subdirectory(DirectX-Headers)

    if(MSVC)
        set_target_properties(DirectX-Headers DirectX-Guids PROPERTIES FOLDER Siesta/ThirdParty/Render)
    endif()
endif()