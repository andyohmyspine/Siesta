#pragma once

#include "Siesta.ObjectAPI.h"
#include "SiestaCore.h"

#include "Fields.h"

#include <functional>

class SObject;
class SObjectInfo;

class SIESTA_OBJECT_API SType
{
public:
	friend class SObjectFactory;

#ifdef SIESTA_EXPOSE_REFLECTION_TOOL
	friend class SFolderParser;
#endif

	virtual ~SType() = default;

	const TString& GetName() const { return m_Name; }
	PSharedPtr<SField> GetField(TStringView Name) const;

protected:
	TString m_Name;

	void AddField(TStringView FieldName, PSharedPtr<SField> Field);

	/**
	 * A function (typically lambda) used to instantiate an object of this class.
	 */
	using InstantiateFunction = std::function<SObject*(const SObjectInfo&)>;
	InstantiateFunction m_Instantiate;

	PHashMap<TStringView, PSharedPtr<SField>> m_Fields;
};