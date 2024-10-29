#include "D3D12SwapChain.h"
#include "D3D12RenderDevice.h"

#include "Interfaces/IPlatformWindow.h"
#include "SiestaRenderD3D12.h"

SD3D12SwapChain::SD3D12SwapChain(SD3D12RenderDevice* Parent, const IPlatformWindow* Window)
	: m_Parent(Parent)
	, m_AssociatedWindow(Window)
{
	DXGI_SWAP_CHAIN_DESC1 Desc{};
	Desc.Width = 0;
	Desc.Height = 0;
	Desc.Format = (DXGI_FORMAT)m_PixelFormat;
	Desc.Stereo = FALSE;
	Desc.SampleDesc = {1, 0};
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_BACK_BUFFER;
	Desc.BufferCount = SIESTA_SWAP_CHAIN_BUFFER_COUNT;
	Desc.Scaling = DXGI_SCALING_STRETCH;
	Desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	Desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

	if (SD3D12RenderDevice::FactoryType* Factory = Parent->GetDXGIFactory())
	{
		PCom<IDXGISwapChain1> SwapChain;
		ThrowIfFailed(Factory->CreateSwapChainForHwnd(
			Parent->GetDirectCommandQueue(),
			(HWND)Window->GetNativeHandle(),
			&Desc,
			nullptr,
			nullptr,
			&SwapChain
		));

		ThrowIfFailed(SwapChain.As(&m_SwapChain));
	}

	AllocateDescriptors();
}

void SD3D12SwapChain::Present()
{
	if (m_SwapChain)
	{
		ThrowIfFailed(m_SwapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING));
		m_CurrentBackBufferIndex = m_SwapChain->GetCurrentBackBufferIndex();
	}

	// TODO: Remove when frame resources done.
	m_Parent->FlushCommandQueue();
}

EPixelFormat SD3D12SwapChain::GetBackBufferPixelFormat() const
{
	return m_PixelFormat;
}

uint32 SD3D12SwapChain::GetCurrentBackBufferIndex() const
{
	return m_CurrentBackBufferIndex;
}

void SD3D12SwapChain::AllocateDescriptors()
{
	if (SD3D12RenderAPI* RAPI = SD3D12RenderAPI::GetOrLoad<SD3D12RenderAPI>())
	{
		if (auto DescriptorPool = RAPI->GetRTVDescriptorPool())
		{
			m_Descriptors = DescriptorPool->AllocateDescriptors(SIESTA_SWAP_CHAIN_BUFFER_COUNT);
			for (uint8 Index = 0; Index < SIESTA_SWAP_CHAIN_BUFFER_COUNT; ++Index)
			{
				PCom<ID3D12Resource> Buffer;
				ThrowIfFailed(m_SwapChain->GetBuffer(Index, IID_PPV_ARGS(&Buffer)));
				if (SD3D12RenderDevice::DeviceType* Device = m_Parent->GetDevice())
				{
					Device->CreateRenderTargetView(Buffer.Get(), nullptr, m_Descriptors.GetCPUHandleAt(Index));
				}
			}
		}
	}
}

