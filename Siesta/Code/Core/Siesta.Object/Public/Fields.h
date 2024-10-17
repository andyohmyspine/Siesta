#pragma once

#include "SiestaCore.h"
#include "Siesta.ObjectAPI.h"

class SObject;

// Ways to get the field value
// 1. By pointer
// 2. By reference
// 3. By value

// Strategies to the field initialization
// 1. Have only one generic class for fields, which has all of the required info
// 2. Have a field base class and use subclasses to initialize virtual calls for field data.
//		a. Probably anonymous classes?
//		b. Or create base classes for all field types that are accessible?

class SIESTA_OBJECT_API SField
{
public:
	virtual ~SField() = default;

	virtual TStringView GetName() const = 0;
	virtual TStringView GetTypeName() const = 0;

	template<typename T>
	const T& GetValueAs(const SObject* Object);

	template<typename T>
	void SetValueAs(SObject* Object, const T& Value);
};

template<typename T>
class SField_TemplateBase : public SField
{
public:
	virtual const T& GetValue(const SObject* Object) const = 0;
	virtual void SetValue(SObject* Object, const T& Value) = 0;
};

template<typename T>
const T& SField::GetValueAs(const SObject* Object)
{
	return static_cast<const SField_TemplateBase<T>*>(this)->GetValue(Object);
}

template<typename T>
void SField::SetValueAs(SObject* Object, const T& Value)
{
	static_cast<SField_TemplateBase<T>*>(this)->SetValue(Object, Value);
}
