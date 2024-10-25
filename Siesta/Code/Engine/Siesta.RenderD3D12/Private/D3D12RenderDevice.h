#pragma once

#include "D3D12Common.h"
#include "Interfaces/SiestaRenderDevice.h"

class SD3D12RenderDevice : public SRenderDevice
{
public:
	SD3D12RenderDevice();
	~SD3D12RenderDevice();

	virtual void FlushCommandQueue() override;
	virtual void SubmitWork_Simple() override;

private:
	void InitCommandBlock();

private:
	PCom<IDXGIFactory6> m_Factory;
	PCom<IDXGIAdapter4> m_Adapter;
	PCom<ID3D12Device5> m_Device;

	PCom<ID3D12CommandQueue> m_DirectCommandQueue;
	PCom<ID3D12GraphicsCommandList> m_GraphicsCommandList;
	PArray<PCom<ID3D12CommandAllocator>, SIESTA_NUM_FRAMES_IN_FLIGHT> m_FrameCommandAllocators;

	PCom<ID3D12Fence> m_Fence;
	uint64 m_FenceValue{};
};