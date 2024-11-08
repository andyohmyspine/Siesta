#pragma once

#include "EngineAPI.h"
#include "Object.h"
#include "SiestaEngine.gen.h"

class IPlatformInterface;
class IPlatformWindow;
class SRenderer;

expose_object() class ENGINE_API SEngine : public SObject
{
	generated_code();

public:
	DECLARE_OBJECT_CONSTRUCTOR(SEngine);
	virtual ~SEngine();

	void BeginMainLoop();

private:
	IPlatformInterface* m_Platform{};
	IPlatformWindow* m_MainWindow{};
	SRenderer* m_Renderer{};

protected:
	TStringView RendererClassName = "SSceneRenderer";
};

ENGINE_API SEngine* CreateEngine(TStringView EngineTypeName = "SEngine");