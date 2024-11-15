#include "HAL/RenderCore/Interfaces/RenderAPI.h"
#include "HAL/RenderCore/Interfaces/RenderDevice.h"
#include "HAL/RenderCore/WindowRenderState.h"

SRenderAPI* SRenderAPI::Instance;

SRenderAPI::SRenderAPI()
{
}

SRenderAPI* SRenderAPI::Get()
{
	if (Instance)
	{
		return Instance;
	}

	Instance = HALCreateRenderAPI();
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
