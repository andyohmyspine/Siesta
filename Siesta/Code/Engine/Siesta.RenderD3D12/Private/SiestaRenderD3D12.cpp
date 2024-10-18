#include "SiestaRenderD3D12.h"
#include "SiestaRenderD3D12.gen.cpp"
#include "D3D12RenderDevice.h"

DEFINE_OBJECT_CONSTRUCTOR(SD3D12RenderAPI)
{
	m_RenderDevice = new SD3D12RenderDevice();
}

SD3D12RenderAPI::~SD3D12RenderAPI()
{
	delete m_RenderDevice;
}
