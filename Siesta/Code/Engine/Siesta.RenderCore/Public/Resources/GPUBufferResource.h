#pragma once

#include "GPUResourceBase.h"

class SIESTA_RENDERCORE_API SGPUBufferResource : public SGPUResourceBase
{
public:
	SGPUBufferResource()
		: SGPUResourceBase("NoNameBuffer", EGPUResourceType::Buffer)
	{
	}

	SGPUBufferResource(const TString& Name)
		: SGPUResourceBase(Name, EGPUResourceType::Buffer)
	{
	}
};