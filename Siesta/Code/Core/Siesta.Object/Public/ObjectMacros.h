#pragma once

#define expose_object(...)
#define expose_field(...)
#define expose_method(...)

// Temporary
#ifndef SIESTA_DONT_EXPAND_GENERATED_CODE
#define generated_code() SIESTA_PASTE_3(SIESTA_FILE, SIESTA_FILE_ID, __LINE__)
#else
#define generated_code()
#endif

