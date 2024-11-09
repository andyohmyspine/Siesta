#pragma once

#include "Renderer/SiestaRenderer.h"
#include "HAL/RenderCore/Resources/GPUBufferResource.h"

class SSceneRenderer : public SRenderer
{
public:
	SSceneRenderer();
	~SSceneRenderer();

	virtual void Render() override;

private:
	SGPUBufferResource* m_TestBuffer;
};