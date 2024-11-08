#pragma once

#include "CoreAll.h"
#include "Object.h"
#include "RenderCoreAPI.h"
#include "SiestaRenderContext.gen.h"

class SRenderAPI;
class SWindowRenderState;

expose_object(abstract)
class RENDERCORE_API SRenderContext : public SObject
{
	generated_code()

public:
	DEFINE_OBJECT_CONSTRUCTOR_INLINE(SRenderContext) {};

	virtual ~SRenderContext() = default;

	virtual void BeginRendering();
	virtual void EndRendering();

	virtual void BeginDrawingToWindow(SWindowRenderState* Window, TColor ClearColor);
	virtual void EndDrawingToWindow();

	inline SWindowRenderState* GetCurrentWindow() const { return m_CurrentWindow; }

private:
	/**
	 * Should be null-ed when finished rendering to the window
	 */
	SWindowRenderState* m_CurrentWindow{};
};