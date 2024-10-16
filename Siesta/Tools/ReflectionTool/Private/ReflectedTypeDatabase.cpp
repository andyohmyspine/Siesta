#include "ReflectedTypeDatabase.h"

SReflectedTypeDatabase::SReflectedTypeDatabase(const PVector<DParsedTypeInfo>& ParsedTypes)
{
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

