add_subdirectory(Code)
add_subdirectory(Tools)
add_subdirectory(Shaders)

if(SIESTA_BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()