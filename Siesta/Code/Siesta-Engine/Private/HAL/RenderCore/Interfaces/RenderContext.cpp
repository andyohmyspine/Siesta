#include "HAL/RenderCore/Interfaces/RenderContext.h"

void SRenderContext::BeginRendering()
{
}

void SRenderContext::EndRendering()
{
}

void SRenderContext::BeginDrawingToWindow(SWindowRenderState* Window, TColor ClearColor)
{
	m_CurrentWindow = Window;
}

void SRenderContext::EndDrawingToWindow()
{
	m_CurrentWindow = nullptr;
}