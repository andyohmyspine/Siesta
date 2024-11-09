#pragma once

#include "Resources/GPUBufferResource.h"

namespace BufferUtils
{
	SGPUBufferResource* CreateBufferResource(const DGPUBufferDesc& Desc);
}