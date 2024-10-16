#include "TypeRegistry.h"

PHashMap<TString, SType*> STypeRegistry::m_Types;

void STypeRegistry::RegisterType(const TString& Name, SType* Type)
{
	m_Types[Name] = Type;
}

SType* STypeRegistry::GetType(const TString& Name)
{
	return m_Types.at(Name);
}

