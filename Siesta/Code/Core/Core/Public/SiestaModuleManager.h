#pragma once

#include "CoreAPI.h"
#include "SiestaTypes.h"

#include <dynalo/dynalo.hpp>

class CORE_API SModule
{
public:
	SModule(const TString& ModulePath);

private:
	dynalo::library m_Library;
};

class CORE_API SModuleManager
{
public:
	static SModule* GetOrLoad(const TString& ModulePath);

private:
	static PHashMap<TString, PUniquePtr<SModule>> m_Modules;
};