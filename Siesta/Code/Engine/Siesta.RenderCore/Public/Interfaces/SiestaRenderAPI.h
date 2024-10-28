#pragma once

#include "Siesta.RenderCoreAPI.h"
#include "Object.h"

#include "SiestaRenderAPI.gen.h"

class SRenderDevice;
class SWindowRenderState;
class IPlatformWindow;

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
public:
	DECLARE_OBJECT_CONSTRUCTOR(SRenderAPI);

	virtual ~SRenderAPI() = default;

	static SRenderAPI* Load(TStringView Name = DEFAULT_RENDER_API);

	inline SRenderDevice* GetDevice() const { return m_RenderDevice; }
	PSharedPtr<SWindowRenderState> CreateWindowRenderState(const IPlatformWindow* Window);

private:
	SModule* m_LoadedModule{};

protected:
	SRenderDevice* m_RenderDevice{};
};