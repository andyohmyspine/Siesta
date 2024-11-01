#pragma once

#include "Siesta.RenderCoreAPI.h"
#include "Resources/GPUBufferResource.h"

namespace BufferUtils
{
	SIESTA_RENDERCORE_API SGPUBufferResource* CreateBufferResource(const DGPUBufferDesc& Desc);
}