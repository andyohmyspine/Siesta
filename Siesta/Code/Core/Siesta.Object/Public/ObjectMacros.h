#pragma once

#define expose_object(...)
#define expose_field(...)
#define expose_method(...)

// Temporary
#define generated_code() SIESTA_PASTE_3(SIESTA_FILE, SIESTA_FILE_ID, __LINE__)
