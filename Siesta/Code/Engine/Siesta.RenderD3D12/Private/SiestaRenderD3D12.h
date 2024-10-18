#pragma once

#include "Interfaces/SiestaRenderAPI.h"
#include "Siesta.RenderD3D12API.h"

#include "SiestaRenderD3D12.gen.h"

expose_object()
class SIESTA_RENDERD3D12_API SD3D12RenderAPI : public SRenderAPI
{
	generated_code()
public:
	DECLARE_OBJECT_CONSTRUCTOR(SD3D12RenderAPI);
	~SD3D12RenderAPI();
};
