#pragma once

#include "Siesta.EngineAPI.h"
#include "Object.h"

#include "SiestaEngine.gen.h"

class IPlatformInterface;
class IPlatformWindow;
class SRenderAPI;

expose_object()
class SIESTA_ENGINE_API SEngine : public SObject
{
	generated_code()

public:
	DECLARE_OBJECT_CONSTRUCTOR(SEngine);
	virtual ~SEngine();

	void BeginMainLoop();

private:
	IPlatformInterface* m_Platform{};
	IPlatformWindow* m_MainWindow{};

	expose_field()
	SRenderAPI* m_RenderAPI;
};

SIESTA_ENGINE_API SEngine* CreateEngine(TStringView EngineTypeName = "SEngine");