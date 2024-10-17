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

	SField* GetField(TStringView Name) const;
	inline TStringView GetName() const { return m_Name; }
	
	virtual TStringView GetParentName() const = 0;
	virtual SType* GetParentType() const = 0;

protected:
	TString m_Name;

	void AddField(TStringView FieldName, SField* Field);

	/**
	 * A function (typically lambda) used to instantiate an object of this class.
	 */
	using InstantiateFunction = std::function<SObject*(const SObjectInfo&)>;
	InstantiateFunction m_Instantiate;

	mutable PHashMap<TStringView, SField*> m_Fields;
	mutable PHashMap<TStringView, SField*> m_ParentFields;
};