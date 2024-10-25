#pragma once

#include "SiestaCore.h"
#include "Siesta.RenderCoreAPI.h"

class SIESTA_RENDERCORE_API SRenderDevice
{
public:
	virtual ~SRenderDevice() = default;

	virtual void FlushCommandQueue() = 0;
	virtual void SubmitWork_Simple() = 0;

protected:
	SRenderDevice() = default;

	TString m_DeviceName;
};