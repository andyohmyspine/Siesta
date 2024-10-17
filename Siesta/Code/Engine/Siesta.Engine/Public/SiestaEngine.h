#pragma once

#include "Siesta.EngineAPI.h"
#include "Object.h"
#include "Interfaces/IPlatform.h"

#include "SiestaEngine.gen.h"

expose_object()
class SIESTA_ENGINE_API SEngine : public SObject
{
	generated_code()

public:
	SEngine(const SObjectInfo& Info);
	virtual ~SEngine();

private:
	IPlatformInterface* m_Platform{};
};

SIESTA_ENGINE_API SEngine* CreateEngine(TStringView EngineTypeName = "SEngine");