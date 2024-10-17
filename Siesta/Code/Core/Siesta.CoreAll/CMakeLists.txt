Siesta_CreateStaticModule(Siesta.CoreAll)

target_link_libraries(Siesta.CoreAll 
    PUBLIC
        Siesta.Config
        Siesta.Core
        Siesta.Object
        Siesta.PlatformCommon )