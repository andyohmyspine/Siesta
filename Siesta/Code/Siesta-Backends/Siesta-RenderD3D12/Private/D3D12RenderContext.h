#pragma once

#include "D3D12Common.h"
#include "HAL/RenderCore/Interfaces/RenderContext.h"

class SD3D12RenderAPI;
class SGPUBufferResource;

class SD3D12RenderContext : public SRenderContext
{
public:
	SD3D12RenderContext(SD3D12RenderAPI* RenderAPI);


	virtual void BeginRendering() override;
	virtual void EndRendering() override;

	virtual void BeginDrawingToWindow(SWindowRenderState* Window, TColor ClearColor) override;
	virtual void EndDrawingToWindow() override;

	void TransitionSingleResource(ID3D12Resource* Resource, D3D12_RESOURCE_STATES From, D3D12_RESOURCE_STATES To, uint32 SubResource = UINT32_MAX);

private:
	SD3D12RenderAPI* m_RenderAPI;
	ID3D12GraphicsCommandList* m_GraphicsCommandList;
};