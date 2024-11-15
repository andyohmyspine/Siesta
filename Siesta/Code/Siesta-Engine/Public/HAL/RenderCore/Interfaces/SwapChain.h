#pragma once

#include "Core.h"
#include "HAL/RenderCore/RenderTypes.h"

class SSwapChain
{
public:
	virtual ~SSwapChain() = default;

	virtual void Present() = 0;
	virtual uint32 GetCurrentBackBufferIndex() const = 0;
	virtual EPixelFormat GetBackBufferPixelFormat() const = 0;
};
