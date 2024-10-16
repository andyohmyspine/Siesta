#pragma once

#include "Siesta.EngineAPI.h"
#include "Object.h"

#include "SiestaEngine.gen.h"

expose_object()
class SIESTA_ENGINE_API SEngine : public SObject
{
	generated_code()

public:
	SEngine(const SObjectInfo& Info);
	virtual ~SEngine();

	expose_field(interesting)
	float Lols = {};

	expose_field(parent, base, lol, coco)
	SObject* OtherObject = nullptr;

	expose_method(somespecifier)
	PVector<TString> GetStrings(const SObject* OtherObject = nullptr) const;
};

SIESTA_ENGINE_API SEngine* CreateEngine();


