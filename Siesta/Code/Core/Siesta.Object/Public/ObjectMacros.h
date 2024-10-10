#pragma once

#define expose_class(...)
#define expose_field(...)

// Temporary
#define expose_class_code(ClassName) inline static SType* StaticType() { return nullptr; }