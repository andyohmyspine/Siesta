Siesta_CreateSharedModule(Siesta.Core)
Siesta_AvoidReflection(Siesta.Core)

target_link_libraries(Siesta.Core PUBLIC Taskflow spdlog dynalo)
target_precompile_headers(Siesta.Core PUBLIC Public/SiestaCorePCH.h)