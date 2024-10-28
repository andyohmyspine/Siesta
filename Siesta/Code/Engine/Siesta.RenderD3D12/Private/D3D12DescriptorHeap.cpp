#include "D3D12DescriptorHeap.h"
#include "SiestaRenderD3D12.h"
#include "D3D12RenderDevice.h"

SD3D12DescriptorHeap::SD3D12DescriptorHeap(SRenderAPI* RenderAPI, EDescriptorHeapType Type, uint32 NumDescriptors, bool ShaderVisible)
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
		}
	}
}

