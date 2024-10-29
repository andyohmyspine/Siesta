#pragma once

#include "SiestaCore.h"
#include "FolderParser.h"

#include <ranges>

class SReflectedTypeDatabase
{
	static SReflectedTypeDatabase* Instance;

public:
	static SReflectedTypeDatabase& Get() { return *Instance; }
	SReflectedTypeDatabase(const PDynArray<DParsedTypeInfo>& ParsedTypes);

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

	const bool IsChildOf(const TString& Derived, const TString& Base) const;

private:
	PHashMap<TString, DParsedTypeInfo> m_ParsedTypes;
};