#include "SiestaEngine.h"

#include "HAL/Platform.h"
#include "Renderer/SiestaRenderer.h"

SEngine::SEngine()
	: m_Platform(WrapUnique<IPlatform, decltype(Detail::IPlatform_Deleter)>(HALCreatePlatform()))
{
	m_MainWindow = m_Platform->CreatePlatformWindow(1280, 720, "Siesta Engine");
	m_Renderer = CreateRenderer(ERendererType::Scene);
}

SEngine::~SEngine()
{
	TerminateRendererLeftovers();

	delete m_MainWindow;
	m_Platform.reset();
}

void SEngine::Run()
{
	while (!m_Platform->ShouldExit())
	{
		m_Platform->Process();

		// Render stuff
		if (m_Renderer)
		{
			m_Renderer->Render();
		}
	}
}
