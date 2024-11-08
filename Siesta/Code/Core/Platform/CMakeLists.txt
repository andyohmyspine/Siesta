Siesta_CreateSharedModule(Platform)

target_link_libraries(
Platform
PUBLIC    
    Core
    Config)

if(WIN32 OR UNIX)
    target_compile_definitions(Platform PRIVATE SIESTA_USE_GLFW)
    target_link_libraries(Platform
        PRIVATE
            glfw)
endif()