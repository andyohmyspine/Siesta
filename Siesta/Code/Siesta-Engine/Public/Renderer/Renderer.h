#pragma once

#include "Core.h"

class SRenderAPI;
class SWindowRenderState;

class SRenderer
{
public:
	SRenderer();
	virtual ~SRenderer();

	virtual void Render() = 0;

protected:
	SRenderAPI* m_RenderAPI;
	PSharedPtr<SWindowRenderState> m_MainWindowRender;
};

enum class ERendererType : uint8
{
	Scene,
};

extern SRenderer* CreateRenderer(ERendererType Type);
extern void TerminateRendererLeftovers();
