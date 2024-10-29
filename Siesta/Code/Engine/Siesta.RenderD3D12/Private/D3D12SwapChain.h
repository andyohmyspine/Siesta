#pragma once

#include "Interfaces/SiestaSwapChain.h"
#include "Siesta.RenderD3D12API.h"

#include "D3D12Common.h"
#include "D3D12DescriptorHeap.h"

class SD3D12RenderDevice;
class IPlatformWindow;

class SIESTA_RENDERD3D12_API SD3D12SwapChain : public SSwapChain
{
public:
	SD3D12SwapChain(SD3D12RenderDevice* Parent, const IPlatformWindow* Window);
	~SD3D12SwapChain();

	virtual void Present() override;
	virtual EPixelFormat GetBackBufferPixelFormat() const override;
	virtual uint32 GetCurrentBackBufferIndex() const override;

	inline CD3DX12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView() const { return m_Descriptors.GetCPUHandleAt(m_CurrentBackBufferIndex); }
	inline ID3D12Resource* GetCurrentBackBufferResource() const { return m_SwapChainBuffers.at(m_CurrentBackBufferIndex).Get(); }

private:
	void AllocateDescriptors();

	void OnResized(const IPlatformWindow* Window, int32 Width, int32 Height);

private:
	SD3D12RenderDevice* m_Parent;
	PCom<IDXGISwapChain4> m_SwapChain;
	const IPlatformWindow* m_AssociatedWindow;

	uint32 m_CurrentBackBufferIndex = 0;
	EPixelFormat m_PixelFormat = PF_R8G8B8A8_UNORM;

	PArray<PCom<ID3D12Resource>, SIESTA_SWAP_CHAIN_BUFFER_COUNT> m_SwapChainBuffers;
	DDescriptorHeapAllocation m_Descriptors{};

	bool m_WaitingForResize = {};
	void Resize();
};