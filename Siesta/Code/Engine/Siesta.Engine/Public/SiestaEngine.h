#pragma once

#include "Siesta.EngineAPI.h"

namespace SE
{
	class SIESTA_ENGINE_API TEngine
	{
	public:
		TEngine();
		virtual ~TEngine();
	};

	SIESTA_ENGINE_API TEngine* CreateEngine();
}

