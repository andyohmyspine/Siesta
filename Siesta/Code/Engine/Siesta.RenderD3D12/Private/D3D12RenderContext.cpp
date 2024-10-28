#include "D3D12RenderContext.h"
#include "D3D12RenderContext.gen.cpp"
#include "Interfaces/SiestaRenderAPI.h"
#include "SiestaRenderD3D12.h"

DEFINE_OBJECT_CONSTRUCTOR(SD3D12RenderContext)
{
	m_RenderAPI = static_cast<SD3D12RenderAPI*>(GetParent());
}

void SD3D12RenderContext::BeginRendering()
{
	TBase::BeginRendering();
}

void SD3D12RenderContext::EndRendering()
{
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
