Siesta_CreateStaticModule(Siesta-Core)

target_link_libraries(Siesta-Core PUBLIC Taskflow spdlog dynalo DirectXMath)
target_precompile_headers(Siesta-Core PUBLIC Public/SiestaCorePCH.h)