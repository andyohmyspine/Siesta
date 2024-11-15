#pragma once

#include "Core.h"

class SRenderAPI;
class SWindowRenderState;

class SRenderContext
{
public:
	SRenderContext() = default;
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