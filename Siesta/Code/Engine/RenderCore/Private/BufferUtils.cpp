#include "BufferUtils.h"

#include "Interfaces/SiestaRenderAPI.h"
#include "Interfaces/SiestaRenderDevice.h"

SGPUBufferResource* BufferUtils::CreateBufferResource(const DGPUBufferDesc& Desc)
{
	SRenderAPI* RenderAPI = SRenderAPI::GetOrLoad();
	SRenderDevice* Device = RenderAPI ? RenderAPI->GetDevice() : nullptr;
	return Device ? Device->CreateBufferResource(Desc) : nullptr;
}
