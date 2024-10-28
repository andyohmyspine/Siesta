#include "Interfaces/SiestaRenderContext.h"
#include "SiestaRenderContext.gen.cpp"

void SRenderContext::BeginRendering()
{
}

void SRenderContext::EndRendering()
{
}

void SRenderContext::BeginDrawingToWindow(SWindowRenderState* Window)
{
	m_CurrentWindow = Window;
}

void SRenderContext::EndDrawingToWindow()
{
	m_CurrentWindow = nullptr;
}
