#include "SiestaEngine.h"

#include "SiestaEngine.gen.cpp"

DEFINE_OBJECT_CONSTRUCTOR(SEngine) {}

SEngine::~SEngine()
{
}

SIESTA_ENGINE_API SEngine* CreateEngine(TStringView EngineTypeName)
{
	return (SEngine*)CreateObject("Engine", STypeRegistry::GetType(TString(EngineTypeName)));
}