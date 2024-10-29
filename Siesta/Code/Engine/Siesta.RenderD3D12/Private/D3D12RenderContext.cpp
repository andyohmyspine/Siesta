#include "D3D12RenderContext.h"
#include "D3D12RenderContext.gen.cpp"
#include "Interfaces/SiestaRenderAPI.h"
#include "SiestaRenderD3D12.h"
#include "D3D12RenderDevice.h"
#include "D3D12SwapChain.h"
#include "WindowRenderState.h"
#include "Interfaces/IPlatformWindow.h"

DEFINE_OBJECT_CONSTRUCTOR(SD3D12RenderContext)
{
	m_RenderAPI = static_cast<SD3D12RenderAPI*>(GetParent());
}

void SD3D12RenderContext::BeginRendering()
{
	TBase::BeginRendering();

	if (SD3D12RenderDevice* Device = static_cast<SD3D12RenderDevice*>(m_RenderAPI->GetDevice()))
	{
		ID3D12CommandAllocator* CA = Device->GetComandAllocatorForCurrentFrameInFlight();
		ThrowIfFailed(CA->Reset());

		m_GraphicsCommandList = Device->GetGraphicsCommandList();
		if (m_GraphicsCommandList)
		{
			ThrowIfFailed(m_GraphicsCommandList->Reset(CA, nullptr));
		}
	}
}

void SD3D12RenderContext::EndRendering()
{
	ThrowIfFailed(m_GraphicsCommandList->Close());

	TBase::EndRendering();
}

void SD3D12RenderContext::BeginDrawingToWindow(SWindowRenderState* Window, TColor ClearColor)
{
	TBase::BeginDrawingToWindow(Window, ClearColor);

	if (SD3D12SwapChain* SwapChain = Window->GetSwapChain<SD3D12SwapChain>())
	{
		ID3D12Resource* BackBuffer = SwapChain->GetCurrentBackBufferResource();
		TransitionSingleResource(BackBuffer, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

		m_GraphicsCommandList->ClearRenderTargetView(SwapChain->GetCurrentBackBufferView(), DirectX::Colors::Blue, 0, nullptr);

		// Set viewport
		Math::XMINT2 WindowSize = Window->GetAssociatedWindow()->GetWindowSize();
		D3D12_VIEWPORT Viewport = 
		{
			.TopLeftX = 0,
			.TopLeftY = 0,
			.Width = (FLOAT)WindowSize.x,
			.Height = (FLOAT)WindowSize.y,
			.MinDepth = 0.0f,
			.MaxDepth = 1.0f,
		};

		m_GraphicsCommandList->RSSetViewports(1, &Viewport);

		D3D12_RECT Scissor =
		{
			.left = 0,
			.top = 0,
			.right = WindowSize.x,
			.bottom = WindowSize.y
		};
		m_GraphicsCommandList->RSSetScissorRects(1, &Scissor);
	}
}

void SD3D12RenderContext::EndDrawingToWindow()
{
	if (SD3D12SwapChain* SwapChain = GetCurrentWindow()->GetSwapChain<SD3D12SwapChain>())
	{
		ID3D12Resource* BackBuffer = SwapChain->GetCurrentBackBufferResource();
		TransitionSingleResource(BackBuffer, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	}

	// This should go last
	TBase::EndDrawingToWindow();
}

void SD3D12RenderContext::TransitionSingleResource(ID3D12Resource* Resource, D3D12_RESOURCE_STATES From, D3D12_RESOURCE_STATES To, uint32 SubResource)
{
	auto Barrier = CD3DX12_RESOURCE_BARRIER::Transition(Resource, From, To, SubResource);
	m_GraphicsCommandList->ResourceBarrier(1, &Barrier);
}
