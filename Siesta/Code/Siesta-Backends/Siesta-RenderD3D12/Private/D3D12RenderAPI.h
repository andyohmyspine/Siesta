#pragma once

#include "HAL/RenderCore/Interfaces/RenderAPI.h"
#include "D3D12RenderContext.h"
#include "D3D12DescriptorHeap.h"

class SD3D12RenderAPI : public SRenderAPI
{
public:
	SD3D12RenderAPI();
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
