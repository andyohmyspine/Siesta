include(GenerateExportHeader)



macro(Siesta_CreateSharedModule _ModuleName)
    add_library(_ModuleName SHARED)

    string(TOUPPER ${_ModuleName} _ModuleName_CAPS)
endmacro()