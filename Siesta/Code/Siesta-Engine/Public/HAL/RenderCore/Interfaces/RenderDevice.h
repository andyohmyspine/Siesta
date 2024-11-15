#pragma once

#include "Core.h"
#include "HAL/RenderCore/Interfaces/SwapChain.h"
#include "HAL/RenderCore/Resources/GPUBufferResource.h"

class IPlatformWindow;

class SRenderDevice
{
public:
	virtual ~SRenderDevice() = default;

	virtual void FlushCommandQueue() = 0;
	virtual void SubmitWork_Simple() = 0;

	virtual PSharedPtr<SSwapChain> CreateSwapChain(const IPlatformWindow* PlatformWindow) = 0;

	virtual void SyncFrameInFlight() = 0;

	virtual SGPUBufferResource* CreateBufferResource(const DGPUBufferDesc& Desc) = 0;

protected:
	SRenderDevice() = default;

	TString m_DeviceName;
};
