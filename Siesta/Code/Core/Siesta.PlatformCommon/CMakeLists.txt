Siesta_CreateSharedModule(Siesta.PlatformCommon)

target_link_libraries(
Siesta.PlatformCommon
PUBLIC    
    Siesta.Core
    Siesta.Config
    Siesta.Math)

if(WIN32 OR UNIX)
    target_compile_definitions(Siesta.PlatformCommon PRIVATE SIESTA_USE_GLFW)
    target_link_libraries(Siesta.PlatformCommon
        PRIVATE
            glfw)
endif()