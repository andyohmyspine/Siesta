#pragma once

#include "Siesta.ObjectAPI.h"
#include "SiestaCore.h"

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

	const TString& GetName() const { return m_Name; }

protected:
	TString m_Name;

	/**
	 * A function (typically lambda) used to instantiate an object of this class.
	 */
	using InstantiateFunction = std::function<SObject* (const SObjectInfo&)>;
	InstantiateFunction m_Instantiate;
};