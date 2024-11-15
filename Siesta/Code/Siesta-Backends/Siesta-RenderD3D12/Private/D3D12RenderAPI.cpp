#include "D3D12RenderAPI.h"
#include "D3D12RenderDevice.h"

uint8 GCurrentFrameInFlight = 0;
uint64 GCurrentFrameIndex = 0;

SD3D12RenderAPI::SD3D12RenderAPI()
{
	D3D12InitializePixelFormatMapping();

	m_RenderDevice = new SD3D12RenderDevice();
	m_RTVDescriptorHeap = MakeShared<SD3D12DescriptorPool>(this, EDescriptorHeapType::RenderTarget, 1024, false);
}

SD3D12RenderAPI::~SD3D12RenderAPI()
{
	delete m_RenderDevice;
}

void SD3D12RenderAPI::InitRenderContext_Impl()
{
	m_RenderContext = new SD3D12RenderContext(this);
}

void SD3D12RenderAPI::OnFrameFinished()
{
	AdvanceFrameInFlight();
	m_RenderDevice->SyncFrameInFlight();

	GCurrentFrameIndex++;
}

SRenderAPI* HALCreateRenderAPI()
{
	return new SD3D12RenderAPI();
}