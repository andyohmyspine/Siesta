add_subdirectory(Code)

add_subdirectory(Tools)

if(SIESTA_BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()