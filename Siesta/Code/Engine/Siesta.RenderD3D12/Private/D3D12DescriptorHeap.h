#pragma once

#include "CoreAll.h"
#include "D3D12Common.h"

enum class EDescriptorHeapType
{
	RenderTarget,
	DepthStencil,
	Uniform,
	Sampler,
};

class SRenderAPI;

class SD3D12DescriptorHeap
{
public:
	SD3D12DescriptorHeap(SRenderAPI* RenderAPI, EDescriptorHeapType Type, uint32 NumDescriptors, bool ShaderVisible);
	virtual ~SD3D12DescriptorHeap() = default;

protected:
	PCom<ID3D12DescriptorHeap> m_DescriptorHeap{};

	CD3DX12_CPU_DESCRIPTOR_HANDLE m_CPUHandle{};
	CD3DX12_GPU_DESCRIPTOR_HANDLE m_GPUHandle{};

	EDescriptorHeapType m_Type{};
	uint32 m_NumDescriptorsTotal{};
	bool m_IsShaderVisible{};

};