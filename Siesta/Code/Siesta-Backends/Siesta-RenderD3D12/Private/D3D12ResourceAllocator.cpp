#include "D3D12ResourceAllocator.h"
#include "D3D12RenderAPI.h"

SD3D12ResourceAllocator* SD3D12ResourceAllocator::Instance;
SD3D12ResourceAllocator::SD3D12ResourceAllocator(PCom<ID3D12Device> Device, PCom<IDXGIAdapter> Adapter)
{
	Instance = this;

	D3D12MA::ALLOCATOR_DESC Desc{};
	Desc.Flags = {};
	Desc.pDevice = Device.Get();
	Desc.pAdapter = Adapter.Get();

	ThrowIfFailed(D3D12MA::CreateAllocator(&Desc, &m_Allocator));
	Debug::Info("D3D12 Resource allocator initialized.");
}

DD3D12ResourceAllocation SD3D12ResourceAllocator::AllocateBuffer(const TString& DebugName, EGPUBufferMutability Mutability, uint64 ByteWidth)
{
	D3D12MA::ALLOCATION_DESC AllocDesc{};
	AllocDesc.Flags |= D3D12MA::ALLOCATION_FLAG_COMMITTED;
	AllocDesc.HeapType = match_enum(Mutability)
	{
		match_case(Static) return D3D12_HEAP_TYPE_DEFAULT;
		match_case(Dynamic) return D3D12_HEAP_TYPE_UPLOAD;
		match_case(Staging) return D3D12_HEAP_TYPE_UPLOAD;
		match_case(Readback) return D3D12_HEAP_TYPE_READBACK;
	}
	end_match;

	auto BufferDesc = CD3DX12_RESOURCE_DESC::Buffer(ByteWidth);

	D3D12_RESOURCE_STATES InitialResourceState = D3D12_RESOURCE_STATE_COMMON;
	if (Mutability == EGPUBufferMutability::Dynamic || Mutability == EGPUBufferMutability::Staging)
	{
		InitialResourceState = D3D12_RESOURCE_STATE_GENERIC_READ;
	}

	DD3D12ResourceAllocation OutAllocation{};
	ThrowIfFailed(m_Allocator->CreateResource(
		&AllocDesc,
		&BufferDesc,
		D3D12_RESOURCE_STATE_COMMON,
		nullptr,
		&OutAllocation.Allocation,
		IID_PPV_ARGS(&OutAllocation.Resource)));

#if !defined(DEBUG) || defined(SIESTA_ENABLE_GPU_VALIDATION)
	if (!DebugName.empty())
	{
		WCHAR OutName[256]{};
		mbstowcs(OutName, DebugName.c_str(), _countof(OutName));
		OutAllocation.Resource->SetName(OutName);
	}
#endif

	return OutAllocation;
}
