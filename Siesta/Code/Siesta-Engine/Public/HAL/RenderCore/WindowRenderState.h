#pragma once

#include "SiestaCore.h"
#include "Interfaces/SiestaSwapChain.h"

class IPlatformWindow;
class SRenderAPI;

class SWindowRenderState
{
public:
	SWindowRenderState(SRenderAPI* RenderAPI, const IPlatformWindow* Window);

	void Present();

	inline SSwapChain* GetSwapChain() const { return m_SwapChain.get(); }

	template<std::derived_from<SSwapChain> T>
	inline T* GetSwapChain() const { return static_cast<T*>(m_SwapChain.get()); }

	inline const IPlatformWindow* GetAssociatedWindow() const { return m_Window; }

private:
	SRenderAPI* m_RenderAPI;
	const IPlatformWindow* m_Window;
	PSharedPtr<SSwapChain> m_SwapChain;
};