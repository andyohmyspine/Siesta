#pragma once

#include "D3D12Common.h"
#include "Resources/GPUBufferResource.h"
#include "Siesta.RenderD3D12API.h"

class SIESTA_RENDERD3D12_API SD3D12BufferResource : public SGPUBufferResource
{
public:
	SD3D12BufferResource(const TString& Name);

private:
	PCom<ID3D12Resource> m_Resource;
};