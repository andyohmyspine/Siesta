#include "RenderGraph/RenderGraphResource.h"
#include "Resources/GPUResourceBase.h"

SRenderGraphResource::~SRenderGraphResource()
{
	if (m_ResourceHandle)
	{
		m_ResourceHandle->Release();
	}
}
