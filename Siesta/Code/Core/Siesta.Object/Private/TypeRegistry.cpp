#include "TypeRegistry.h"

static TMutex TypeMutex;

STypeRegistry& STypeRegistry::Get()
{
	static STypeRegistry Out;
	return Out;
}

void STypeRegistry::RegisterType(const TString& Name, SType* Type)
{
	Get().m_Types.insert({Name, Type});
}

SType* STypeRegistry::GetType(const TString& Name)
{
	if(Get().m_Types.contains(Name))
		return Get().m_Types.at(Name);

	return nullptr;
}
