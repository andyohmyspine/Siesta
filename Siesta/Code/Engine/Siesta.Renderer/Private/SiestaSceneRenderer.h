#pragma once

#include "SiestaRenderer.h"

#include "SiestaSceneRenderer.gen.h"
#include "Resources/GPUBufferResource.h"

expose_object() class SIESTA_RENDERER_API SSceneRenderer : public SRenderer
{
	generated_code();

public:
	DECLARE_OBJECT_CONSTRUCTOR(SSceneRenderer);
	~SSceneRenderer();

	virtual void Render() override;

private:
	SGPUBufferResource* m_TestBuffer;
};