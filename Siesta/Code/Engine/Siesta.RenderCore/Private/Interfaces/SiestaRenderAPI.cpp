#include "Interfaces/SiestaRenderAPI.h"
#include "SiestaRenderAPI.gen.cpp"
#include "WindowRenderState.h"
#include "Interfaces/SiestaRenderDevice.h"

SRenderAPI* SRenderAPI::Instance;

DEFINE_OBJECT_CONSTRUCTOR(SRenderAPI)
{ }

SRenderAPI* SRenderAPI::GetOrLoad(TStringView Name /*= DEFAULT_RENDER_API*/)
{
	if (Instance)
	{
		return Instance;
	}

	if (Name == DEFAULT_RENDER_API)
	{
		SModuleManager::GetOrLoad(DEFAULT_RENDER_API_MODULE);
	}
	else
	{
		Debug::Critical("Loading arbitrary render APIs is currently unsupported.");
	}

	Instance = CreateObject<SRenderAPI>("RenderAPI", STypeRegistry::GetType(TString(Name)));
	return Instance;
}

SRenderAPI::~SRenderAPI()
{
	delete m_RenderContext;
}

PSharedPtr<SWindowRenderState> SRenderAPI::CreateWindowRenderState(const IPlatformWindow* Window)
{
	// TODO: Cache the state.
	return MakeShared<SWindowRenderState>(this, Window);
}

SRenderContext* SRenderAPI::GetRenderContext()
{
	if (!m_RenderContext)
	{
		InitRenderContext_Impl();
	}

	return m_RenderContext;
}

void SRenderAPI::SubmitDeviceWorkHelper()
{
	m_RenderDevice->SubmitWork_Simple();
}
