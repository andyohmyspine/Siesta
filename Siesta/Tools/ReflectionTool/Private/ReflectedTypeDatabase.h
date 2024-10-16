#pragma once

#include "SiestaCore.h"
#include "FolderParser.h"

#include <ranges>

class SReflectedTypeDatabase
{
public:
	SReflectedTypeDatabase(const PVector<DParsedTypeInfo>& ParsedTypes);

	inline const DParsedTypeInfo* TryGetType(const TString& Name) const 
	{
		if (m_ParsedTypes.contains(Name))
		{
			return &m_ParsedTypes.at(Name);
		}

		return nullptr;
	}

	inline const auto GetOnlyTypes() const
	{
		return m_ParsedTypes | std::views::values;
	}

private:
	PHashMap<TString, DParsedTypeInfo> m_ParsedTypes;
};