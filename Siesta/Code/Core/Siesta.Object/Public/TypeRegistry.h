#pragma once

#include "Siesta.ObjectAPI.h"

#include "SiestaCore.h"
#include "Type.h"

class SIESTA_OBJECT_API STypeRegistry
{
public:
	static STypeRegistry& Get();

	static void RegisterType(const TString& Name, SType* Type);
	static SType* GetType(const TString& Name);

private:	
	PHashMap<TString, SType*> m_Types;
};

#define SIESTA_REGISTER_OBJECT_TYPE(TypeName) namespace Internal { struct SIESTA_PASTE_2(DInternalTypeRegistrar_, TypeName) \
{ SIESTA_PASTE_2(DInternalTypeRegistrar_, TypeName)() { STypeRegistry::RegisterType(#TypeName, new SIESTA_PASTE_2(SType_, TypeName)); } }; \
static SIESTA_PASTE_2(DInternalTypeRegistrar_, TypeName) SIESTA_PASTE_2(DInternalRegistrar_, TypeName) {}; }