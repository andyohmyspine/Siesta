#pragma once

#include "Renderer/SiestaRenderer.h"
#include "HAL/RenderCore/Resources/GPUBufferResource.h"

class SShader;

class SSceneRenderer : public SRenderer
{
public:
	SSceneRenderer();
	~SSceneRenderer();

	virtual void Render() override;

private:
	SGPUBufferResource* m_TestBuffer;

	SShader* m_TestVS;
	SShader* m_TestPS;
};