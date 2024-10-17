#include "ReflectedTypeDatabase.h"

SReflectedTypeDatabase* SReflectedTypeDatabase::Instance;

SReflectedTypeDatabase::SReflectedTypeDatabase(const PVector<DParsedTypeInfo>& ParsedTypes)
{
	Instance = this;

	for (const DParsedTypeInfo& Type : ParsedTypes)
	{
		if (m_ParsedTypes.contains(Type.Name))
		{
			Debug::Critical("The database already contains a type named '{}'. Please choose another name.", Type.Name);
		}

		m_ParsedTypes[Type.Name] = Type;
	}

	Debug::Info("Type database generated with {} types.", m_ParsedTypes.size());
}

const bool SReflectedTypeDatabase::IsChildOf(const TString& Derived, const TString& Base) const
{
	if (const DParsedTypeInfo* DerivedType = TryGetType(Derived))
	{
		if (DerivedType->Name == Base)
		{
			return true;
		}
		else if (DerivedType->Parent.empty())
		{
			return false;
		}
		else if (DerivedType->Parent == Base)
		{
			return true;
		}
		else
		{
			return IsChildOf(DerivedType->Parent, Base);
		}
	}

	return false;
}

