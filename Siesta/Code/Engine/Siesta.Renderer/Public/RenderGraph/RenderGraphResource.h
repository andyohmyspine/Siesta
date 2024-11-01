#pragma once

#include "CoreAll.h"
#include "Siesta.RendererAPI.h"

enum class ERenderGraphResourceType : uint8
{
};

class SGPUResourceBase;

class SIESTA_RENDERER_API SRenderGraphResource
{
public:
	SRenderGraphResource() = default;
	virtual ~SRenderGraphResource();

	inline void SetPersistent(bool NewIsPersistent) { m_IsPersistent = NewIsPersistent; }
	inline bool IsPersistent() const { return m_IsPersistent; }

private:
	/** The handle to the resource. May be unallocated. */
	SGPUResourceBase* m_ResourceHandle{};

	/** Set to true if this resource should be destroyed only if the application is being closed. */
	bool m_IsPersistent : 1 {};
};