#pragma once

#include "SiestaCore.h"
#include "RenderCoreAPI.h"
#include "Interfaces/SiestaSwapChain.h"
#include "Resources/GPUBufferResource.h"

class IPlatformWindow;

class RENDERCORE_API SRenderDevice
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