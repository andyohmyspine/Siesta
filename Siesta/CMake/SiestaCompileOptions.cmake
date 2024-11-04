macro(Siesta_AddCompileOptionWithMacro _Name _DefaultValue)
    option(${_Name} "" ${_DefaultValue})
    if(${_Name})
        add_definitions(-D${_Name})
    endif()
endmacro()

Siesta_AddCompileOptionWithMacro(SIESTA_BUILD_DIST OFF)
Siesta_AddCompileOptionWithMacro(SIESTA_ENABLE_GPU_VALIDATION OFF)