#pragma once

#include "D3D12Common.h"
#include "Interfaces/SiestaRenderDevice.h"
#include "D3D12ResourceAllocator.h"

class SD3D12BufferResource;

struct DPendingBufferTransfer
{
	D3D12_RESOURCE_STATES InitialState;
	D3D12_RESOURCE_STATES FinalState;
	SD3D12BufferResource* DstResource;

private:
	SD3D12BufferResource* InternalSrcResource;
	friend class SD3D12RenderDevice;
};

class SD3D12RenderDevice : public SRenderDevice
{
public:
	using DeviceType = ID3D12Device5;
	using FactoryType = IDXGIFactory6;
	using AdapterType = IDXGIAdapter4;

	SD3D12RenderDevice();
	~SD3D12RenderDevice();

	virtual void FlushCommandQueue() override;
	virtual void SubmitWork_Simple() override;

	inline FactoryType* GetDXGIFactory() const { return m_Factory.Get(); }
	inline DeviceType* GetDevice() const { return m_Device.Get(); }
	inline ID3D12CommandQueue* GetDirectCommandQueue() const { return m_DirectCommandQueue.Get(); }
	inline ID3D12Fence* GetFence() const { return m_Fence.Get(); }

	virtual PSharedPtr<SSwapChain> CreateSwapChain(const IPlatformWindow* PlatformWindow) override;

	ID3D12CommandAllocator* GetComandAllocatorForCurrentFrameInFlight() const;
	ID3D12GraphicsCommandList* GetGraphicsCommandList() const;

	virtual void SyncFrameInFlight() override;

	inline auto GetFenceValue() const { return m_FenceValue; }
	inline auto GetFrameFenceValue() const { return m_FrameFenceValues[GCurrentFrameInFlight]; }

	virtual SGPUBufferResource* CreateBufferResource(const DGPUBufferDesc& Desc) override;

	void AddPendingBufferTransfer(DPendingBufferTransfer NewTransfer);
	void ClearPendingTransfers();
	void ClearPendingTransfers_ForCurrentFrame();
	
	void FlushPendingTransfers(ID3D12GraphicsCommandList* Cmd);
	void ClearSubmittedTransfers_ForCurrentFrame();
	void ClearSubmittedTransfers();

private:
	void InitCommandBlock();

private:
	PCom<FactoryType> m_Factory;
	PCom<AdapterType> m_Adapter;
	PCom<DeviceType> m_Device;

	PCom<ID3D12CommandQueue> m_DirectCommandQueue;

	PCom<ID3D12GraphicsCommandList> m_GraphicsCommandList;
	PArray<PCom<ID3D12CommandAllocator>, SIESTA_NUM_FRAMES_IN_FLIGHT> m_FrameCommandAllocators{};
	PArray<uint64, SIESTA_NUM_FRAMES_IN_FLIGHT> m_FrameFenceValues{};

	PCom<ID3D12Fence> m_Fence;
	uint64 m_FenceValue{};

	PSharedPtr<SD3D12ResourceAllocator> m_ResourceAllocator;

	// This is where pending transfers live.
	PArray<PDynArray<DPendingBufferTransfer>, SIESTA_NUM_FRAMES_IN_FLIGHT> m_PendingBufferTransfers;

	// This is where already submitted transfers live.
	PArray<PDynArray<PDynArray<DPendingBufferTransfer>>, SIESTA_NUM_FRAMES_IN_FLIGHT> m_SubmittedBufferTransfers;
};

void EnqueueBufferTransfer(DPendingBufferTransfer Transfer);