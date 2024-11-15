#include "Resources/D3D12BufferResource.h"

#include "D3D12RenderContext.h"
#include "D3D12RenderAPI.h"
#include "D3D12RenderDevice.h"
#include "D3D12SwapChain.h"
#include "HAL/Platform.h"

#include "HAL/RenderCore/Interfaces/RenderAPI.h"
#include "HAL/RenderCore/WindowRenderState.h"

SD3D12RenderContext::SD3D12RenderContext(SD3D12RenderAPI* RenderAPI)
	: m_RenderAPI(RenderAPI)
{
}

void SD3D12RenderContext::BeginRendering()
{
	SRenderContext::BeginRendering();

	if (SD3D12RenderDevice* Device = static_cast<SD3D12RenderDevice*>(m_RenderAPI->GetDevice()))
	{
		if (Device->GetFrameFenceValue() != 0 && Device->GetFence()->GetCompletedValue() < Device->GetFrameFenceValue())
		{
			// Wait for fence
			HANDLE EventHandle = CreateEventEx(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
			if (EventHandle)
			{
				ThrowIfFailed(Device->GetFence()->SetEventOnCompletion(Device->GetFrameFenceValue(), EventHandle));
				WaitForSingleObject(EventHandle, INFINITE);
				CloseHandle(EventHandle);
			}
		}

		Device->NotifyAndClearSubmittedTransfers_ForCurrentFrame();
		ID3D12CommandAllocator* CA = Device->GetComandAllocatorForCurrentFrameInFlight();
		ThrowIfFailed(CA->Reset());
		m_GraphicsCommandList = Device->GetGraphicsCommandList();
		if (m_GraphicsCommandList)
		{
			ThrowIfFailed(m_GraphicsCommandList->Reset(CA, nullptr));

			if (auto Device = m_RenderAPI->GetDevice<SD3D12RenderDevice>())
			{
				Device->FlushPendingTransfers(m_GraphicsCommandList);
			}
		}
	}
}

void SD3D12RenderContext::EndRendering()
{
	ThrowIfFailed(m_GraphicsCommandList->Close());

	SRenderContext::EndRendering();
}

void SD3D12RenderContext::BeginDrawingToWindow(SWindowRenderState* Window, TColor ClearColor)
{
	SRenderContext::BeginDrawingToWindow(Window, ClearColor);

	if (SD3D12SwapChain* SwapChain = Window->GetSwapChain<SD3D12SwapChain>())
	{
		ID3D12Resource* BackBuffer = SwapChain->GetCurrentBackBufferResource();
		TransitionSingleResource(BackBuffer, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

		m_GraphicsCommandList->ClearRenderTargetView(SwapChain->GetCurrentBackBufferView(), ClearColor, 0, nullptr);

		// Set viewport
		Math::XMINT2 WindowSize = Window->GetAssociatedWindow()->GetWindowSize();
		D3D12_VIEWPORT Viewport = {
			.TopLeftX = 0,
			.TopLeftY = 0,
			.Width = (FLOAT)WindowSize.x,
			.Height = (FLOAT)WindowSize.y,
			.MinDepth = 0.0f,
			.MaxDepth = 1.0f,
		};

		m_GraphicsCommandList->RSSetViewports(1, &Viewport);

		D3D12_RECT Scissor = {
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
	SRenderContext::EndDrawingToWindow();
}

void SD3D12RenderContext::TransitionSingleResource(ID3D12Resource* Resource, D3D12_RESOURCE_STATES From, D3D12_RESOURCE_STATES To, uint32 SubResource)
{
	auto Barrier = CD3DX12_RESOURCE_BARRIER::Transition(Resource, From, To, SubResource);
	m_GraphicsCommandList->ResourceBarrier(1, &Barrier);
}