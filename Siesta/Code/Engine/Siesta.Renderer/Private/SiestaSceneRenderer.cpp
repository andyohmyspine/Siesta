#include "SiestaSceneRenderer.h"

#include "Interfaces/SiestaRenderContext.h"
#include "Interfaces/SiestaRenderAPI.h"

#include "SiestaSceneRenderer.gen.cpp"
#include "WindowRenderState.h"

DEFINE_OBJECT_CONSTRUCTOR(SSceneRenderer)
{

}

SSceneRenderer::~SSceneRenderer()
{

}

void SSceneRenderer::Render()
{
	// Rendering happens here only if RC is valid
	if (SRenderContext* RC = m_RenderAPI->GetRenderContext())
	{
		RC->BeginRendering();

		// Setup window to render to
		RC->BeginDrawingToWindow(m_MainWindowRender.get(), Math::Colors::Black);
		{
			
		}
		RC->EndDrawingToWindow();
		RC->EndRendering();

		m_RenderAPI->SubmitDeviceWorkHelper();
	}

	m_MainWindowRender->Present();
	m_RenderAPI->OnFrameFinished();
}