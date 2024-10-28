#pragma once

#include "Interfaces/SiestaSwapChain.h"
#include "Siesta.RenderD3D12API.h"

#include "D3D12Common.h"

class SD3D12RenderDevice;
class IPlatformWindow;

class SIESTA_RENDERD3D12_API SD3D12SwapChain : public SSwapChain
{
public:
	SD3D12SwapChain(SD3D12RenderDevice* Parent, const IPlatformWindow* Window);

	virtual void Present() override;
	virtual EPixelFormat GetBackBufferPixelFormat() const override;
	virtual uint32 GetCurrentBackBufferIndex() const override;

private:
	SD3D12RenderDevice* m_Parent;
	PCom<IDXGISwapChain4> m_SwapChain;
	const IPlatformWindow* m_AssociatedWindow;

	uint32 m_CurrentBackBufferIndex = 0;
	EPixelFormat m_PixelFormat = PF_R8G8B8A8_UNORM;
};