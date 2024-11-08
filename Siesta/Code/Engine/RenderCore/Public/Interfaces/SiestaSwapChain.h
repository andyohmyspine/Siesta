#pragma once

#include "SiestaCore.h"
#include "RenderCoreAPI.h"
#include "SiestaRenderTypes.h"

class RENDERCORE_API SSwapChain
{
public:
	virtual ~SSwapChain() = default;

	virtual void Present() = 0;
	virtual uint32 GetCurrentBackBufferIndex() const = 0;
	virtual EPixelFormat GetBackBufferPixelFormat() const = 0;
};