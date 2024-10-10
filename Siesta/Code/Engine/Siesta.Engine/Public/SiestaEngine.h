#pragma once

#include "Siesta.EngineAPI.h"


class SIESTA_ENGINE_API SEngine
{
public:
	SEngine();
	virtual ~SEngine();
};

SIESTA_ENGINE_API SEngine* CreateEngine();


