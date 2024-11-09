#include "HAL/RenderCore/BufferUtils.h"

#include "HAL/RenderCore/Interfaces/SiestaRenderAPI.h"
#include "HAL/RenderCore/Interfaces/SiestaRenderDevice.h"

SGPUBufferResource* BufferUtils::CreateBufferResource(const DGPUBufferDesc& Desc)
{
	SRenderAPI* RenderAPI = SRenderAPI::Get();
	SRenderDevice* Device = RenderAPI ? RenderAPI->GetDevice() : nullptr;
	return Device ? Device->CreateBufferResource(Desc) : nullptr;
}
