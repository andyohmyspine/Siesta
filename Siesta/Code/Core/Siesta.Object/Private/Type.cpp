#include "Type.h"

SField* SType::GetField(TStringView Name) const
{
	if(m_Fields.contains(Name))
		return m_Fields.at(Name);
	else if(m_ParentFields.contains(Name))
		return m_ParentFields.at(Name);
	// Try to find field in parent and cache it
	else if (SType* ParentType = GetParentType())
	{
		auto Field = ParentType->GetField(Name);
		m_ParentFields[Name] = Field;
		return Field;
	}
	else
	{
		Debug::Warning("Could not find a field with name '{}' in type '{}'", Name, m_Name);
		return nullptr;
	}

	return nullptr;
}

void SType::AddField(TStringView FieldName, SField* Field)
{
	m_Fields[FieldName] = Field;
}
