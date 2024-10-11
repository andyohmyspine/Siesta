#pragma once

#include "Siesta.ObjectAPI.h"

#include "SiestaCore.h"
#include "Type.h"

class SIESTA_OBJECT_API STypeRegistry
{
public:
	

private:	
	PHashMap<TString, SType*> m_Types;
};