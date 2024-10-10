Siesta_CreateSharedModule(Siesta.Core)

target_link_libraries(Siesta.Core PUBLIC Taskflow)
target_precompile_headers(Siesta.Core PUBLIC Public/SiestaCorePCH.h)