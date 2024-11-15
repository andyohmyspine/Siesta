#pragma once

#include "D3D12Common.h"

#define D3D12MA_D3D12_HEADERS_ALREADY_INCLUDED
#include "D3D12MemAlloc.h"
#include "HAL/RenderCore/Resources/GPUBufferResource.h"

struct DD3D12ResourceAllocation
{
	PCom<ID3D12Resource> Resource;
	PCom<D3D12MA::Allocation> Allocation;
};

class SD3D12ResourceAllocator
{
	static SD3D12ResourceAllocator* Instance;
public:
	static SD3D12ResourceAllocator& Get() { return *Instance; }

	SD3D12ResourceAllocator(PCom<ID3D12Device> Device, PCom<IDXGIAdapter> Adapter);

	DD3D12ResourceAllocation AllocateBuffer(const TString& DebugName, EGPUBufferMutability Mutability, uint64 ByteWidth);

private:
	PCom<D3D12MA::Allocator> m_Allocator;
};