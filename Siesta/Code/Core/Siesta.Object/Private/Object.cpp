#include "Object.h"
#include "Type.h"

#include "Object.gen.cpp"

SObject::SObject(const SObjectInfo& Info)
{
}

SObject* SObjectFactory::CreateObject(const TString& Name, SType* Type, SObject* Parent /*= nullptr*/)
{
	SObjectInfo ObjectInfo{};
	ObjectInfo.Name = Name;
	ObjectInfo.Type = Type;
	ObjectInfo.Parent = Parent;
	
	if (Type->m_Instantiate)
	{
		return Type->m_Instantiate(ObjectInfo);
	}

	return nullptr;
}
