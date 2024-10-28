#include "D3D12RenderContext.h"
#include "D3D12RenderContext.gen.cpp"
#include "Interfaces/SiestaRenderAPI.h"
#include "SiestaRenderD3D12.h"
#include "D3D12RenderDevice.h"

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

void SD3D12RenderContext::BeginDrawingToWindow(SWindowRenderState* Window)
{
	TBase::BeginDrawingToWindow(Window);
}

void SD3D12RenderContext::EndDrawingToWindow()
{
	// This should go last
	TBase::EndDrawingToWindow();
}
