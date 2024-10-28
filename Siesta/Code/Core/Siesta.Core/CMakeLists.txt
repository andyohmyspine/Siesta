Siesta_CreateSharedModule(Siesta.Core)
Siesta_AvoidReflection(Siesta.Core)

target_link_libraries(Siesta.Core PUBLIC Taskflow spdlog dynalo DirectXMath)
target_precompile_headers(Siesta.Core PUBLIC Public/SiestaCorePCH.h)
target_compile_definitions(Siesta.Core PUBLIC _XM_NO_XMVECTOR_OVERLOADS_)