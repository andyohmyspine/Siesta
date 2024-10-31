add_library(DXC INTERFACE)
target_include_directories(DXC INTERFACE Include)

if(WIN32)
    target_link_directories(DXC INTERFACE Bin/Win64)
    target_link_libraries(DXC INTERFACE dxcompiler)
endif()

set(DXC_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "")

function(Siesta_CopyDXCBinaries _Target)
    set(DxcBinaries)
    if(WIN32)
        list(APPEND DxcBinaries ${DXC_DIR}/Bin/Win64/dxcompiler.dll)
        list(APPEND DxcBinaries ${DXC_DIR}/Bin/Win64/dxil.dll)
    endif()

    foreach(Binary IN LISTS DxcBinaries)
        get_filename_component(BinaryName ${Binary} NAME_WE)
        add_custom_command(TARGET ${_Target} POST_BUILD 
            COMMAND 
                ${CMAKE_COMMAND} -E copy_if_different ${Binary} $<TARGET_FILE_DIR:${_Target}>/${BinaryName}.dll)
    endforeach()
endfunction()