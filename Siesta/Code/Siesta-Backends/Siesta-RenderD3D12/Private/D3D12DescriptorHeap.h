#pragma once

#include "Core.h"
#include "D3D12Common.h"

/**
 * The idea with descriptor heaps is that they need to be split into separate partitions
 */

enum class EDescriptorHeapType
{
	RenderTarget,
	DepthStencil,
	Uniform,
	Sampler,
};

inline constexpr TStringView ToString(EDescriptorHeapType Type)
{
	return match_enum(Type)
	{
		match_case(RenderTarget) return "RTV";
		match_case(DepthStencil) return "DSV";
		match_case(Uniform) return "CBV_SRV_UAV";
		match_case(Sampler) return "Sampler";
	} end_match;
}

class SRenderAPI;

struct DDescriptorHeapAllocation
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE CPUHandle{};
	CD3DX12_GPU_DESCRIPTOR_HANDLE GPUHandle{};
	uint32 NumDescriptorsAllocated{};
	uint32 DescriptorIncrementSize{};
	bool ShaderVisible{};

	inline CD3DX12_CPU_DESCRIPTOR_HANDLE GetCPUHandleAt(uint32 Index) const
	{
		auto OutHandle = CPUHandle;
		OutHandle.Offset(Index, DescriptorIncrementSize);
		return OutHandle;
	}

	inline CD3DX12_GPU_DESCRIPTOR_HANDLE GetGPUHandleAt(uint32 Index) const
	{
		auto OutHandle = GPUHandle;
		OutHandle.Offset(Index, DescriptorIncrementSize);
		return OutHandle;
	}

	inline bool IsValid() const 
	{
		return NumDescriptorsAllocated > 0;
	}

	inline operator bool() const
	{
		return IsValid();
	}
};

/**
 * Descriptor heap is a simple wrapper around D3D12DescriptorHeap. 
 * It has ability to allocate descriptors. It is meant to be used by a higher level abstractions, that
 * subdivide the heap into parts.
 */
class SD3D12DescriptorHeap
{
public:
	SD3D12DescriptorHeap(SRenderAPI* RenderAPI, EDescriptorHeapType Type, uint32 NumDescriptors, bool ShaderVisible);
	virtual ~SD3D12DescriptorHeap() = default;

	virtual DDescriptorHeapAllocation AllocateDescriptors(uint32 NumDescriptors);

	inline uint32 GetNumDescriptors() const { return m_NumDescriptorsTotal; }
	inline uint32 GetDescriptorIncrementSize() const { return m_DescriptorIncrementSize; }
	inline bool IsShaderVisible() const { return m_IsShaderVisible; }
	inline EDescriptorHeapType GetDescriptorHeapType() const { return m_Type; }

protected:
	PCom<ID3D12DescriptorHeap> m_DescriptorHeap{};

	CD3DX12_CPU_DESCRIPTOR_HANDLE m_CPUHandle{};
	CD3DX12_GPU_DESCRIPTOR_HANDLE m_GPUHandle{};

	EDescriptorHeapType m_Type{};
	uint32 m_NumDescriptorsTotal{};
	uint32 m_DescriptorIncrementSize{};
	bool m_IsShaderVisible{};

	uint32 m_NumDescriptorsAllocated{};
};

enum class DD3D12DescriptorPartitionHandle : uint32
{
};

class SD3D12DescriptorPartition
{
public:
	SD3D12DescriptorPartition(const TString& Name, const DDescriptorHeapAllocation& Allocation);

private:
	TString m_PartitionName;
	DDescriptorHeapAllocation m_Allocation;
};

/**
 * Descriptor pool is a higher-level abstraction around the DescriptorHeap.
 * It allows for subdivision of the descriptor heap (e.g. to sort descriptors by frequency of use)
 */
class SD3D12DescriptorPool
{
public:
	SD3D12DescriptorPool(SRenderAPI* RenderAPI, EDescriptorHeapType Type, uint32 NumDescriptorsTotal, bool ShaderVisible);

	inline DDescriptorHeapAllocation AllocateDescriptors(uint32 NumDescriptors)
	{
		return m_Heap.AllocateDescriptors(NumDescriptors);
	}

	DD3D12DescriptorPartitionHandle CreatePartition(uint32 NumDescriptors);

private:
	SD3D12DescriptorHeap m_Heap;

	PDynArray<PUniquePtr<SD3D12DescriptorPartition>> m_Partitions;
};