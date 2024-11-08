#include "SiestaRenderer.h"
#include "Interfaces/SiestaRenderAPI.h"
#include "Interfaces/IPlatform.h"
#include "SiestaRenderer.gen.cpp"

DEFINE_OBJECT_CONSTRUCTOR(SRenderer)
{
	m_RenderAPI = SRenderAPI::GetOrLoad();
	m_MainWindowRender = m_RenderAPI->CreateWindowRenderState(IPlatformInterface::Get().GetMainWindow());
}

SRenderer::~SRenderer()
{
	m_MainWindowRender.reset();
	delete m_RenderAPI;
}
