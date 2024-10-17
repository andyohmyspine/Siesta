#pragma once

#include "Siesta.EngineAPI.h"
#include "Object.h"

#include "SiestaEngine.gen.h"

class IPlatformInterface;
class IPlatformWindow;

expose_object()
class SIESTA_ENGINE_API SEngine : public SObject
{
	generated_code()

public:
	SEngine(const SObjectInfo& Info);
	virtual ~SEngine();

	void BeginMainLoop();

private:
	IPlatformInterface* m_Platform{};
	IPlatformWindow* m_MainWindow{};
};

SIESTA_ENGINE_API SEngine* CreateEngine(TStringView EngineTypeName = "SEngine");