#include "HAL/RenderCore/WindowRenderState.h"
#include "HAL/RenderCore/Interfaces/RenderAPI.h"
#include "HAL/RenderCore/Interfaces/RenderDevice.h"

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

