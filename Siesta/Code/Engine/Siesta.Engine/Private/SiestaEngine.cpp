#include "SiestaEngine.h"
#include "Interfaces/IPlatform.h"
#include "Interfaces/SiestaRenderAPI.h"

#include "SiestaEngine.gen.cpp"

DEFINE_OBJECT_CONSTRUCTOR(SEngine) 
{
	m_Platform = IPlatformInterface::Create();
	m_MainWindow = m_Platform->CreatePlatformWindow(1280, 720, "SiestaEngine");

	m_RenderAPI = SRenderAPI::GetOrLoad();
	m_MainWindowRender = m_RenderAPI->CreateWindowRenderState(m_MainWindow);
}

SEngine::~SEngine()
{
	delete m_RenderAPI;
	delete m_MainWindow;
	delete m_Platform;
}

void SEngine::BeginMainLoop()
{
	while (!m_Platform->ShouldExit())
	{
		m_Platform->Process();

		m_MainWindowRender->Present();
	}
}

SEngine* CreateEngine(TStringView EngineTypeName)
{
	return (SEngine*)CreateObject("Engine", STypeRegistry::GetType(TString(EngineTypeName)));
}