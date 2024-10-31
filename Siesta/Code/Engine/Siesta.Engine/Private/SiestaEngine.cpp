#include "SiestaEngine.h"
#include "Interfaces/IPlatform.h"
#include "SiestaRenderer.h"

#include "SiestaEngine.gen.cpp"

DEFINE_OBJECT_CONSTRUCTOR(SEngine) 
{
	m_Platform = IPlatformInterface::Create();
	m_MainWindow = m_Platform->CreatePlatformWindow(1280, 720, "SiestaEngine");

	// Create renderer
	// Load renderer module
	SModuleManager::GetOrLoad("Siesta.Renderer");

	m_Renderer = CreateObject<SRenderer>("Renderer", STypeRegistry::GetType(TString(RendererClassName)));
}

SEngine::~SEngine()
{
	delete m_Renderer;
	delete m_MainWindow;
	delete m_Platform;
}

void SEngine::BeginMainLoop()
{
	while (!m_Platform->ShouldExit())
	{
		m_Platform->Process();

		if (m_Renderer)
		{
			m_Renderer->Render();
		}
	}
}

SEngine* CreateEngine(TStringView EngineTypeName)
{
	return (SEngine*)CreateObject("Engine", STypeRegistry::GetType(TString(EngineTypeName)));
}