#include "SiestaEngine.h"

#include "HAL/Platform.h"

SEngine::SEngine()
	: m_Platform(WrapUnique<IPlatform, decltype(Detail::IPlatform_Deleter)>(HALCreatePlatform()))
{
	m_MainWindow = m_Platform->CreatePlatformWindow(1280, 720, "Siesta Engine");
}

SEngine::~SEngine()
{
}

void SEngine::Run()
{
	while (!m_Platform->ShouldExit())
	{
		m_Platform->Process();

		// Render stuff
	}
}
