#include "HAL/RenderCore/BufferUtils.h"

#include "HAL/RenderCore/Interfaces/RenderAPI.h"
#include "HAL/RenderCore/Interfaces/RenderDevice.h"

SGPUBufferResource* BufferUtils::CreateBufferResource(const DGPUBufferDesc& Desc)
{
	SRenderAPI* RenderAPI = SRenderAPI::Get();
	SRenderDevice* Device = RenderAPI ? RenderAPI->GetDevice() : nullptr;
	return Device ? Device->CreateBufferResource(Desc) : nullptr;
}
