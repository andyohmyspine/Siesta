#include "Object.h"
#include "Type.h"

SObject::SObject(const SObjectInfo& Info)
{
}

SObject* SObjectFactory::CreateObject(const TString& Name, SType* Type, SObject* Parent /*= nullptr*/)
{
	SObjectInfo ObjectInfo{};
	ObjectInfo.Name = Name;
	ObjectInfo.Type = Type;
	ObjectInfo.Parent = Parent;
	
	if (Type->Instantiate)
	{
		return Type->Instantiate(ObjectInfo);
	}

	return nullptr;
}
