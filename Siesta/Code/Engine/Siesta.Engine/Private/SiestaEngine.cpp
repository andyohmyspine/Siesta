#include "SiestaEngine.h"

SIESTA_ENGINE_API SEngine* CreateEngine()
{
	return new SEngine({});
}

SEngine::SEngine(const SObjectInfo& Info)
	: SObject(Info)
{

}

SEngine::~SEngine()
{

}

PVector<TString> SEngine::GetStrings(const SObject* OtherObject) const
{
	return {};
}
