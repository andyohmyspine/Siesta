#pragma once

#include "Siesta.RenderCoreAPI.h"
#include "Object.h"

#include "SiestaRenderAPI.gen.h"

class SRenderDevice;
class SWindowRenderState;
class IPlatformWindow;
class SRenderContext;

#ifdef WIN32
#define DEFAULT_RENDER_API "SD3D12RenderAPI"
#define DEFAULT_RENDER_API_MODULE "Siesta.RenderD3D12"
#else
#error "Unsupported platform"
#endif

expose_object(abstract)
class SIESTA_RENDERCORE_API SRenderAPI : public SObject
{
	generated_code()
	
	static SRenderAPI* Instance;
public:
	DECLARE_OBJECT_CONSTRUCTOR(SRenderAPI);

	virtual ~SRenderAPI();

	static SRenderAPI* GetOrLoad(TStringView Name = DEFAULT_RENDER_API);

	inline SRenderDevice* GetDevice() const { return m_RenderDevice; }
	PSharedPtr<SWindowRenderState> CreateWindowRenderState(const IPlatformWindow* Window);

	SRenderContext* GetRenderContext();

private:
	SModule* m_LoadedModule{};

protected:
	SRenderDevice* m_RenderDevice{};
	SRenderContext* m_RenderContext;

	virtual void InitRenderContext_Impl() {}
};