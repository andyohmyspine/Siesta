#pragma once

#include "Siesta.EngineAPI.h"
#include "Object.h"

expose_object()
class SIESTA_ENGINE_API SEngine : public SObject
{
	generated_code()

public:
	SEngine(const SObjectInfo& Info);
	virtual ~SEngine();

	expose_field(interesting)
	float Lols = {};
};

SIESTA_ENGINE_API SEngine* CreateEngine();


