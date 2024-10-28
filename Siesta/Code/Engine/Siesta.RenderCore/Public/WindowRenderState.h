#pragma once

#include "CoreAll.h"
#include "Siesta.RenderCoreAPI.h"
#include "Interfaces/SiestaSwapChain.h"

class IPlatformWindow;
class SRenderAPI;

class SIESTA_RENDERCORE_API SWindowRenderState
{
public:
	SWindowRenderState(SRenderAPI* RenderAPI, const IPlatformWindow* Window);

	void Present();

private:
	SRenderAPI* m_RenderAPI;
	const IPlatformWindow* m_Window;
	PSharedPtr<SSwapChain> m_SwapChain;
};