#include "SiestaRenderD3D12.h"
#include "D3D12RenderDevice.h"

#include "SiestaRenderD3D12.gen.cpp"

uint8 GCurrentFrameInFlight = 0;

DEFINE_OBJECT_CONSTRUCTOR(SD3D12RenderAPI)
{
	m_RenderDevice = new SD3D12RenderDevice();

	m_RTVDescriptorHeap = MakeShared<SD3D12DescriptorPool>(this, EDescriptorHeapType::RenderTarget, 1024, false);
}

SD3D12RenderAPI::~SD3D12RenderAPI()
{
	delete m_RenderDevice;
}

void SD3D12RenderAPI::InitRenderContext_Impl()
{
	m_RenderContext = CreateObject<SD3D12RenderContext>("RenderContext", this);
}
