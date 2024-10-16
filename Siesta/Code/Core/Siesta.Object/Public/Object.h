#pragma once

#include "Siesta.ObjectAPI.h"
#include "SiestaCore.h"
#include "ObjectMacros.h"

#include "Object.gen.h"

class SType;

class SIESTA_OBJECT_API SObjectInfo
{
	friend class SObject;
	friend class SObjectFactory;
private:
	TString Name;
	SType* Type{};
	SObject* Parent{};
};

/**
 * Base class of any reflectable object.
 */
expose_object(abstract) 
class SIESTA_OBJECT_API SObject
{
	generated_code()

public:
	virtual ~SObject() = default;

	inline SType* GetType() const { return m_Type; }
	inline SObject* GetParent() const { return m_Parent; }

protected:
	SObject(const SObjectInfo& Info);

private:
	SType* m_Type = nullptr;
	SObject* m_Parent = nullptr;
	friend class SObjectFactory;
};

class SIESTA_OBJECT_API SObjectFactory
{
public:
	static SObject* CreateObject(const TString& Name, SType* Type, SObject* Parent = nullptr);

	template<std::derived_from<SObject> T>
	static T* CreateObject(const TString& Name, SObject* Parent)
	{
		return static_cast<T*>(CreateObject(Name, T::StaticType(), Parent));
	}
};

