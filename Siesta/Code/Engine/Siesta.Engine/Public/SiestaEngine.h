#pragma once

#include "Siesta.EngineAPI.h"
#include "Object.h"

expose_class
class SIESTA_ENGINE_API SEngine : public SObject
{
	expose_code()
public:
	SEngine(const SObjectInfo& Info);
	virtual ~SEngine();
};

SIESTA_ENGINE_API SEngine* CreateEngine();


