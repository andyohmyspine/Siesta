#pragma once

#include "HAL/RenderCore/Resources/GPUTextureResource.h"

#include "D3D12Common.h"
#include "D3D12ResourceAllocator.h"

class SD3D12TextureResource : public SGPUTextureResource
{
public:
	SD3D12TextureResource(const DGPUTextureDesc& Desc);

private:
	DD3D12ResourceAllocation m_ResourceAllocation{};
};