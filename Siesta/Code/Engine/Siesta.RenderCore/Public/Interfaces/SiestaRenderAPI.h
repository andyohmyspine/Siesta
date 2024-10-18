#pragma once

#include "Siesta.RenderCoreAPI.h"
#include "Object.h"

#include "SiestaRenderAPI.gen.h"

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

private:
	SModule* m_LoadedModule{};
};