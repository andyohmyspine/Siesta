#include "WindowRenderState.h"
#include "Interfaces/SiestaRenderAPI.h"
#include "Interfaces/SiestaRenderDevice.h"

SWindowRenderState::SWindowRenderState(SRenderAPI* RenderAPI, const IPlatformWindow* Window)
	: m_RenderAPI(RenderAPI)
	, m_Window(Window)
{
	m_SwapChain = RenderAPI->GetDevice()->CreateSwapChain(Window);
}

void SWindowRenderState::Present()
{
	m_SwapChain->Present();
}

