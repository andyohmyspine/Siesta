#pragma once

#include "Interfaces/SiestaRenderAPI.h"
#include "RenderD3D12API.h"
#include "D3D12RenderContext.h"

#include "D3D12DescriptorHeap.h"
#include "D3D12RenderAPI.gen.h"

expose_object()
class RENDERD3D12_API SD3D12RenderAPI : public SRenderAPI
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

	virtual void OnFrameFinished() override;

private:
	PSharedPtr<SD3D12DescriptorPool> m_RTVDescriptorHeap;
};
