#include "SiestaEngine.h"

#include "SiestaEngine.gen.cpp"

DEFINE_OBJECT_CONSTRUCTOR(SEngine) {}

SEngine::~SEngine()
{

}

PVector<TString> SEngine::GetStrings(const SObject* OtherObject) const
{
	return {};
}

SIESTA_ENGINE_API SEngine* CreateEngine(TStringView EngineTypeName)
{
	return (SEngine*)CreateObject("Engine", STypeRegistry::GetType(TString(EngineTypeName)));
}