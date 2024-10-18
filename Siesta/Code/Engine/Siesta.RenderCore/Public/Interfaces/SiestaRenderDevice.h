#pragma once

#include "SiestaCore.h"
#include "Siesta.RenderCoreAPI.h"

class SIESTA_RENDERCORE_API SRenderDevice
{
public:
	virtual ~SRenderDevice() = default;

protected:
	SRenderDevice() = default;

	TString m_DeviceName;
};