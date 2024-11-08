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

// Class specifiers
#define abstract

// Method specifiers

// Field specifiers
#define getter
#define setter

#define DECLARE_OBJECT_CONSTRUCTOR(Name) Name(const SObjectInfo& Info)
#define DEFINE_OBJECT_CONSTRUCTOR(Name) Name::Name(const SObjectInfo& Info) : TBase(Info)
#define DEFINE_OBJECT_CONSTRUCTOR_INLINE(Name) Name(const SObjectInfo& Info) : TBase(Info)