include(GenerateExportHeader)

macro(Siesta_LoadModuleFiles)
    file(GLOB_RECURSE _ModuleFiles 
            ${CMAKE_CURRENT_LIST_DIR}/Public/*.h 
            ${CMAKE_CURRENT_LIST_DIR}/Public/*.cpp
            ${CMAKE_CURRENT_LIST_DIR}/Private/*.h
            ${CMAKE_CURRENT_LIST_DIR}/Private/*.cpp
        )
endmacro()

macro(Siesta_DefaultModuleProperties _ModuleName)
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${_ModuleFiles})
    target_compile_features(${_ModuleName} PUBLIC cxx_std_20)

    # Get module folder
    cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH _ParentPath)
    cmake_path(RELATIVE_PATH _ParentPath BASE_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE _ParentPath_RELATIVE)
    set_target_properties(${_ModuleName} PROPERTIES FOLDER ${_ParentPath_RELATIVE})
    target_include_directories(${_ModuleName} PUBLIC Public PRIVATE Private)
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
        EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/${_ModuleName}/${_ModuleName}API.h
    )
    target_include_directories(${_ModuleName} PUBLIC ${CMAKE_BINARY_DIR}/${_ModuleName})
    
endmacro()


#####################################################################
# CREATE EXE MODULE
#####################################################################
macro(Siesta_CreateExeModule _ModuleName)
    Siesta_LoadModuleFiles()
    add_executable(${_ModuleName} ${_ModuleFiles})
    Siesta_DefaultModuleProperties(${_ModuleName})
endmacro()