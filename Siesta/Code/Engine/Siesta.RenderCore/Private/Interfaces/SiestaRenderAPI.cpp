#include "Interfaces/SiestaRenderAPI.h"
#include "SiestaRenderAPI.gen.cpp"

DEFINE_OBJECT_CONSTRUCTOR(SRenderAPI)
{ }

SRenderAPI* SRenderAPI::Load(TStringView Name /*= DEFAULT_RENDER_API*/)
{
	if (Name == DEFAULT_RENDER_API)
	{
		SModuleManager::Load(DEFAULT_RENDER_API_MODULE);
	}
	else
	{
		Debug::Critical("Loading arbitrary render APIs is currently unsupported.");
	}

	return CreateObject<SRenderAPI>("RenderAPI", STypeRegistry::GetType(TString(Name)));
}