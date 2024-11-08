#pragma once

#include "SiestaTypes.h"

#include <dynalo/dynalo.hpp>

class SModule
{
public:
	SModule(const TString& ModulePath);

private:
	dynalo::library m_Library;
};

class SModuleManager
{
public:
	static SModule* GetOrLoad(const TString& ModulePath);

private:
	static PHashMap<TString, PUniquePtr<SModule>> m_Modules;
};