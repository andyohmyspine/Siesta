include(GenerateExportHeader)

macro(Siesta_LoadModuleFiles)
    file(GLOB_RECURSE _ModuleFiles 
            ${CMAKE_CURRENT_LIST_DIR}/Public/*.h 
            ${CMAKE_CURRENT_LIST_DIR}/Public/*.cpp
            ${CMAKE_CURRENT_LIST_DIR}/Public/*.inl
            ${CMAKE_CURRENT_LIST_DIR}/Private/*.h
            ${CMAKE_CURRENT_LIST_DIR}/Private/*.cpp
            ${CMAKE_CURRENT_LIST_DIR}/Private/*.inl)

        
endmacro()

macro(Siesta_DefaultModuleProperties _ModuleName)
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${_ModuleFiles})
    target_compile_features(${_ModuleName} PUBLIC cxx_std_20)

    # Get module folder
    cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH _ParentPath)
    cmake_path(RELATIVE_PATH _ParentPath BASE_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE _ParentPath_RELATIVE)
    set_target_properties(${_ModuleName} PROPERTIES FOLDER ${_ParentPath_RELATIVE})
    target_include_directories(${_ModuleName} PUBLIC Public PRIVATE Private ${CMAKE_BINARY_DIR}/Generated/Sources)
    target_compile_definitions(${_ModuleName} PRIVATE SIESTA_REFLECTED_TARGET)
endmacro()

macro(Siesta_AvoidReflection _ModuleName)
    target_compile_definitions(${_ModuleName} PRIVATE SIESTA_AVOID_REFLECTION)
endmacro()

#####################################################################
# CREATE SHARED MODULE
#####################################################################
macro(Siesta_CreateSharedModule _ModuleName)
    Siesta_LoadModuleFiles()
    add_library(${_ModuleName} SHARED ${_ModuleFiles})

    Siesta_DefaultModuleProperties(${_ModuleName})
    string(TOUPPER ${_ModuleName} _ModuleName_CAPS)
    GENERATE_EXPORT_HEADER(
        ${_ModuleName}
        EXPORT_MACRO_NAME ${_ModuleName_CAPS}_API
        EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/Generated/${_ModuleName}API.h
    )
    target_include_directories(${_ModuleName} PUBLIC ${CMAKE_BINARY_DIR}/Generated)
    
endmacro()

#####################################################################
# CREATE STATIC MODULE
#####################################################################
macro(Siesta_CreateStaticModule _ModuleName)
    Siesta_LoadModuleFiles()
    add_library(${_ModuleName} STATIC ${_ModuleFiles})
    Siesta_DefaultModuleProperties(${_ModuleName})    
endmacro()


#####################################################################
# CREATE EXE MODULE
#####################################################################
macro(Siesta_CreateExeModule _ModuleName)
    Siesta_LoadModuleFiles()
    add_executable(${_ModuleName} ${_ModuleFiles})
    Siesta_DefaultModuleProperties(${_ModuleName})
endmacro()