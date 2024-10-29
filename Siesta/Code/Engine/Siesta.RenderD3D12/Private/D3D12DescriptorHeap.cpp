#include "D3D12DescriptorHeap.h"
#include "D3D12RenderAPI.h"
#include "D3D12RenderDevice.h"

SD3D12DescriptorHeap::SD3D12DescriptorHeap(SRenderAPI* RenderAPI, EDescriptorHeapType Type, uint32 NumDescriptors, bool ShaderVisible)
	: m_Type(Type)
	, m_NumDescriptorsTotal(NumDescriptors)
	, m_IsShaderVisible(ShaderVisible)
{
	D3D12_DESCRIPTOR_HEAP_DESC HeapDesc{};
	HeapDesc.NumDescriptors = NumDescriptors;
	HeapDesc.Type = match_enum(Type)
	{
		match_case(RenderTarget) return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		match_case(DepthStencil) return D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		match_case(Uniform) return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		match_case(Sampler) return D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
		match_default();
	} end_match;

	if (auto RAPI = static_cast<SD3D12RenderAPI*>(RenderAPI))
	{
		if (auto Device = static_cast<SD3D12RenderDevice*>(RAPI->GetDevice()))
		{
			ThrowIfFailed(Device->GetDevice()->CreateDescriptorHeap(&HeapDesc, IID_PPV_ARGS(&m_DescriptorHeap)));
			m_DescriptorIncrementSize = Device->GetDevice()->GetDescriptorHandleIncrementSize(HeapDesc.Type);

			Debug::Info("(D3D12) Created {} descriptor heap with {} descriptors. Shader visible: {}", ToString(Type), NumDescriptors, ShaderVisible);

			m_CPUHandle = m_DescriptorHeap->GetCPUDescriptorHandleForHeapStart();
			if (ShaderVisible)
			{
				m_GPUHandle = m_DescriptorHeap->GetGPUDescriptorHandleForHeapStart();
			}
		}
	}
}

DDescriptorHeapAllocation SD3D12DescriptorHeap::AllocateDescriptors(uint32 NumDescriptors)
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE OutCPUHandle = m_CPUHandle;
	OutCPUHandle.Offset(m_NumDescriptorsAllocated, m_DescriptorIncrementSize);

	DDescriptorHeapAllocation OutAlloc
	{
		.CPUHandle = OutCPUHandle,
		.NumDescriptorsAllocated = NumDescriptors,
		.DescriptorIncrementSize = m_DescriptorIncrementSize,
		.ShaderVisible = m_IsShaderVisible
	};

	if (m_IsShaderVisible)
	{
		CD3DX12_GPU_DESCRIPTOR_HANDLE OutGPUHandle = m_GPUHandle;
		OutGPUHandle.Offset(m_NumDescriptorsAllocated, m_DescriptorIncrementSize);
		OutAlloc.GPUHandle = OutGPUHandle;
	}

	m_NumDescriptorsAllocated += NumDescriptors;
	return OutAlloc;
}

SD3D12DescriptorPool::SD3D12DescriptorPool(SRenderAPI* RenderAPI, EDescriptorHeapType Type, uint32 NumDescriptorsTotal, bool ShaderVisible)
	: m_Heap(RenderAPI, Type, NumDescriptorsTotal, ShaderVisible)
{
}
