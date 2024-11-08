#pragma once

#include "RenderCoreAPI.h"
#include "Resources/GPUBufferResource.h"

namespace BufferUtils
{
	RENDERCORE_API SGPUBufferResource* CreateBufferResource(const DGPUBufferDesc& Desc);
}