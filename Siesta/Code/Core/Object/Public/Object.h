#pragma once

#include "ObjectAPI.h"
#include "SiestaCore.h"
#include "ObjectMacros.h"
#include "Type.h"

#include "Object.gen.h"

class OBJECT_API SObjectInfo
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
class OBJECT_API SObject
{
	generated_code()

public:
	virtual ~SObject() = default;

	inline SType* GetType() const { return m_Type; }
	inline SObject* GetParent() const { return m_Parent; }

	inline const TString& GetName() const { return m_Name; }

protected:
	SObject(const SObjectInfo& Info);

private:
	SType* m_Type = nullptr;
	SObject* m_Parent = nullptr;
	TString m_Name{};
	friend class SObjectFactory;
};

class OBJECT_API SObjectFactory
{
public:
	static SObject* CreateObject(const TString& Name, SType* Type, SObject* Parent = nullptr);

	template<std::derived_from<SObject> T>
	static T* CreateObject(const TString& Name, SObject* Parent = nullptr)
	{
		return static_cast<T*>(CreateObject(Name, T::GetStaticType(), Parent));
	}
};

inline SObject* CreateObject(const TString& Name, SType* Type, SObject* Parent = nullptr)
{
	return SObjectFactory::CreateObject(Name, Type, Parent);
}

template<std::derived_from<SObject> T>
inline PUniquePtr<T> CreateObjectUnique(const TString& Name, SType* Type, SObject* Parent = nullptr)
{
	return WrapUnique((T*)CreateObject(Name, Type, Parent));
}

template<std::derived_from<SObject> T>
static T* CreateObject(const TString& Name, SObject* Parent = nullptr)
{
	return static_cast<T*>(CreateObject(Name, T::GetStaticType(), Parent));
}

template<std::derived_from<SObject> T>
static T* CreateObject(const TString& Name, SType* Type, SObject* Parent = nullptr)
{
	return static_cast<T*>(CreateObject(Name, Type, Parent));
}

template<typename T>
const T& GetFieldValueChecked(const SObject* Object, TStringView Name)
{
	const SType* Type = Object->GetType();
	const SField* Field = Type->GetField(Name);
	if (!Field)
	{
		Debug::Critical("Could not find field with name '{}' in type '{}'", Name, Type->GetName());
	}
	return Field->GetValueAs<T>(Object);
}

template<typename T>
const T* TryGetFieldValue(const SObject* Object, TStringView Name)
{
	const SType* Type = Object->GetType();
	SField* Field = Type->GetField(Name);
	if (!Field)
	{
		Debug::Warning("Could not find field with name '{}' in type '{}'", Name, Type->GetName());
		return nullptr;
	}
	
	return &Field->GetValueAs<T>(Object);
}

template<typename T>
void SetFieldValue(SObject* Object, TStringView Name, const T& Value)
{
	SType* Type = Object->GetType();
	auto Field = Type->GetField(Name);
	Field->SetValueAs<T>(Object, Value);
}
