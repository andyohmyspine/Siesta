#include "SiestaSceneRenderer.h"

#include "Interfaces/SiestaRenderContext.h"
#include "Interfaces/SiestaRenderAPI.h"

#include "WindowRenderState.h"

#include "BufferUtils.h"

#include "SiestaSceneRenderer.gen.cpp"

DEFINE_OBJECT_CONSTRUCTOR(SSceneRenderer)
{
	DGPUBufferDesc BufferDesc{
		.DebugName = "TestBuffer",
		.ByteSize = 1024,
		.ByteStride = 1024,
		.Mutability = EGPUBufferMutability::Static,
		.Usage = BU_Vertex,
	};

	char data[1024] = {};
	m_TestBuffer = BufferUtils::CreateBufferResource(BufferDesc);
	m_TestBuffer->WriteData(data, 1024, 0);
}

SSceneRenderer::~SSceneRenderer()
{
	m_TestBuffer->Release();
}

void SSceneRenderer::Render()
{
	// Rendering happens here only if RC is valid
	if (SRenderContext* RC = m_RenderAPI->GetRenderContext())
	{
		RC->BeginRendering();

		// Setup window to render to
		RC->BeginDrawingToWindow(m_MainWindowRender.get(), Math::Colors::SlateBlue);
		{
			
		}
		RC->EndDrawingToWindow();
		RC->EndRendering();

		m_RenderAPI->SubmitDeviceWorkHelper();
	}

	m_MainWindowRender->Present();
	m_RenderAPI->OnFrameFinished();
}