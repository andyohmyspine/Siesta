#include "Type.h"

PSharedPtr<SField> SType::GetField(TStringView Name) const
{
	if(m_Fields.contains(Name))
		return m_Fields.at(Name);

	return nullptr;
}

void SType::AddField(TStringView FieldName, PSharedPtr<SField> Field)
{
	m_Fields[FieldName] = Field;
}
