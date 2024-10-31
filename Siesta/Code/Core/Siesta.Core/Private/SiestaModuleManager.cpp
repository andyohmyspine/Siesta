#include "SiestaModuleManager.h"

PHashMap<TString, PUniquePtr<SModule>> SModuleManager::m_Modules;

SModule::SModule(const TString& ModulePath)
	: m_Library(dynalo::to_native_name(ModulePath))
{
}

SModule* SModuleManager::GetOrLoad(const TString& ModulePath)
{
	if (!m_Modules.contains(ModulePath))
	{
		m_Modules[ModulePath] = WrapUnique(new SModule(ModulePath));
	}

	return m_Modules.at(ModulePath).get();
}