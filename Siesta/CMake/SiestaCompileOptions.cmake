macro(Siesta_AddCompileOptionWithMacro _Name _DefaultValue)
    option(${_Name} "" ${_DefaultValue})
    if(${_Name})
        add_definitions(-D${_Name})
    endif()
endmacro()

macro(Siesta_AddMacro _Name)
    option(${_Name} "" ON)
    add_definitions(-D${_Name})
endmacro()

Siesta_AddCompileOptionWithMacro(SIESTA_BUILD_EDITOR ON)
Siesta_AddCompileOptionWithMacro(SIESTA_BUILD_DIST OFF)
Siesta_AddCompileOptionWithMacro(SIESTA_ENABLE_GPU_VALIDATION OFF)

if(WIN32)
    Siesta_AddMacro(SIESTA_PLATFORM_WINDOWS)
    Siesta_AddMacro(SIESTA_USE_D3D12)
endif()

if(WIN32 OR UNIX)
    Siesta_AddMacro(SIESTA_PLATFORM_DESKTOP)
endif()