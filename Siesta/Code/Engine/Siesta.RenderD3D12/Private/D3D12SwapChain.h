#pragma once

#include "Interfaces/SiestaSwapChain.h"
#include "Siesta.RenderD3D12API.h"

#include "D3D12Common.h"

class SD3D12RenderDevice;

class SIESTA_RENDERD3D12_API SD3D12SwapChain : public SSwapChain
{
public:
	

private:
	SD3D12RenderDevice* m_Parent;
	PCom<IDXGISwapChain4> m_SwapChain;
};