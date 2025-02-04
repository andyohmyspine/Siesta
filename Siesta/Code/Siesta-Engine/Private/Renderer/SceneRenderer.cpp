#include "SceneRenderer.h"

#include "HAL/RenderCore/Interfaces/RenderContext.h"
#include "HAL/RenderCore/Interfaces/RenderAPI.h"
#include "HAL/RenderCore/WindowRenderState.h"
#include "HAL/RenderCore/BufferUtils.h"

#include "HAL/RenderCore/ShaderRegistry.h"

SSceneRenderer::SSceneRenderer()
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

	m_TestVS = SShaderRegistry::GetShader("Test/Test.hlsl", EShaderStage::VertexShader);
	m_TestPS = SShaderRegistry::GetShader("Test/Test.hlsl", EShaderStage::PixelShader);
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
		RC->BeginDrawingToWindow(m_MainWindowRender.get(), Math::Colors::DarkSlateGray);
		{
			
		}
		RC->EndDrawingToWindow();
		RC->EndRendering();

		m_RenderAPI->SubmitDeviceWorkHelper();
	}

	m_MainWindowRender->Present();
	m_RenderAPI->OnFrameFinished();
}