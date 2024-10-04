#include "SiestaEngine.h"

namespace SE
{
	SIESTA_ENGINE_API TEngine* CreateEngine()
	{
		return new TEngine;
	}

	TEngine::TEngine()
	{

	}

	TEngine::~TEngine()
	{

	}

}