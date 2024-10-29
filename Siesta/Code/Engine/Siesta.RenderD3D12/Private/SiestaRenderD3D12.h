#pragma once

#include "Interfaces/SiestaRenderAPI.h"
#include "Siesta.RenderD3D12API.h"
#include "D3D12RenderContext.h"

#include "SiestaRenderD3D12.gen.h"
#include "D3D12DescriptorHeap.h"

expose_object()
class SIESTA_RENDERD3D12_API SD3D12RenderAPI : public SRenderAPI
{
	generated_code()

public:
	DECLARE_OBJECT_CONSTRUCTOR(SD3D12RenderAPI);
	~SD3D12RenderAPI();

	virtual void InitRenderContext_Impl() override;

	inline PSharedPtr<SD3D12DescriptorPool> GetRTVDescriptorPool() const
	{
		return m_RTVDescriptorHeap;
	}

private:
	PSharedPtr<SD3D12DescriptorPool> m_RTVDescriptorHeap;
};
