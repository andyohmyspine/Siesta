Siesta_CreateStaticModule(Siesta-Engine)

target_link_libraries(Siesta-Engine PUBLIC Siesta-Core)

if(WIN32 OR UNIX)
    target_link_libraries(Siesta-Engine PUBLIC glfw)
endif()