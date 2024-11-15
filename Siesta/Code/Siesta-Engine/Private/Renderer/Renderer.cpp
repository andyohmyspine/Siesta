#include "Renderer/Renderer.h"
#include "HAL/RenderCore/Interfaces/RenderAPI.h"
#include "HAL/Platform.h"

SRenderer::SRenderer()
{
	m_RenderAPI = SRenderAPI::Get();
	m_MainWindowRender = m_RenderAPI->CreateWindowRenderState(IPlatform::Get().GetMainWindow());
}

SRenderer::~SRenderer()
{
	m_MainWindowRender.reset();
	delete m_RenderAPI;
}

#include "RendererResolver.h"
SRenderer* CreateRenderer(ERendererType Type)
{
	return SRendererResolver::GetOrCreate(Type);
}

extern void TerminateRendererLeftovers()
{	
	SRendererResolver::Terminate();
}
