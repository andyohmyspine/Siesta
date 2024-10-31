#pragma once

#include "CoreAll.h"
#include "Siesta.RendererAPI.h"
#include "SiestaRenderer.gen.h"

class SRenderAPI;
class SWindowRenderState;

expose_object(abstract) class SIESTA_RENDERER_API SRenderer : public SObject
{
	generated_code();

public:
	DECLARE_OBJECT_CONSTRUCTOR(SRenderer);
	~SRenderer();

	virtual void Render() = 0;

protected:
	SRenderAPI* m_RenderAPI;
	PSharedPtr<SWindowRenderState> m_MainWindowRender;
};