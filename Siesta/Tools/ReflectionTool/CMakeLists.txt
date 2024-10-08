Siesta_CreateExeModule(Siesta.ReflectionTool)

target_link_libraries(Siesta.ReflectionTool PRIVATE Siesta.Core Siesta.Object)

# Select all reflected targets from the Siesta codebase.
# And add them to the reflection database
set(Siesta_ReflectedTargets)
macro(Siesta_AddAllTargetsToReflection _Directory)
    get_property(_Targets DIRECTORY "${_Directory}" PROPERTY BUILDSYSTEM_TARGETS)
    foreach(_Target IN LISTS _Targets)
        get_target_property(_TargetDefines ${_Target} COMPILE_DEFINITIONS)
        if("SIESTA_REFLECTED_TARGET" IN_LIST _TargetDefines)
            set(Siesta_ReflectedTargets ${Siesta_ReflectedTargets} ${_Target})
        endif()
    endforeach()

    get_property(_Subdirectories DIRECTORY "${_Directory}" PROPERTY SUBDIRECTORIES)
    foreach(_Subdirectory IN LISTS _Subdirectories)
        Siesta_AddAllTargetsToReflection("${_Subdirectory}")
    endforeach()
endmacro()

# Generate a variable that will be defined in the ReflectionTool.
# This means that reflection tool will be rebuilt everytime new project is added, but that's OK
Siesta_AddAllTargetsToReflection(${CMAKE_SOURCE_DIR} Siesta_ReflectedTargets)
set(_GlobalReflectionDatabase)
foreach(_ReflectedTarget IN LISTS Siesta_ReflectedTargets)
    get_target_property(_TargetSourceDir ${_ReflectedTarget} SOURCE_DIR)
    list(APPEND _GlobalReflectionDatabase "${_TargetSourceDir}|")
endforeach()

string(REPLACE "\\" "/" _GlobalReflectionDatabase ${_GlobalReflectionDatabase})
target_compile_definitions(Siesta.ReflectionTool PRIVATE 
    SIESTA_REFLECTION_FOLDERS="${_GlobalReflectionDatabase}"
    SIESTA_REFLECTION_OUTPUT="${CMAKE_BINARY_DIR}/Generated/Headers"
    SIESTA_EXPOSE_REFLECTION_TOOL)