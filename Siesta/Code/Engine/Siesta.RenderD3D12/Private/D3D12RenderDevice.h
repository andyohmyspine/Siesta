#pragma once

#include "D3D12Common.h"
#include "Interfaces/SiestaRenderDevice.h"

class SD3D12RenderDevice : public SRenderDevice
{
public:
	SD3D12RenderDevice();
	~SD3D12RenderDevice();

private:
	PCom<IDXGIFactory6> m_Factory;
	PCom<IDXGIAdapter4> m_Adapter;
	PCom<ID3D12Device5> m_Device;
};