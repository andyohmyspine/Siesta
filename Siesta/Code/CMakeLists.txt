add_subdirectory(Core)
add_subdirectory(Engine)

if(SIESTA_BUILD_EDITOR)
    add_subdirectory(Editor)
endif()