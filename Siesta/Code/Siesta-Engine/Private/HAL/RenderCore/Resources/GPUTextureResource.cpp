#include "HAL/RenderCore/Resources/GPUTextureResource.h"

SGPUTextureResource::SGPUTextureResource(const DGPUTextureDesc& Desc)
	: SGPUResourceBase(Desc.DebugName, EGPUResourceType::Texture)
{
}
