#pragma once

#include "D3D12Common.h"
#include "Siesta.RenderD3D12API.h"

#define D3D12MA_D3D12_HEADERS_ALREADY_INCLUDED
#include "D3D12MemAlloc.h"
#include "Resources/GPUBufferResource.h"

struct DD3D12ResourceAllocation
{
	PCom<ID3D12Resource> Resource;
	PCom<D3D12MA::Allocation> Allocation;

};

class SIESTA_RENDERD3D12_API SD3D12ResourceAllocator
{
	static SD3D12ResourceAllocator* Instance;
public:
	static SD3D12ResourceAllocator& Get() { return *Instance; }

	SD3D12ResourceAllocator(PCom<ID3D12Device> Device, PCom<IDXGIAdapter> Adapter);

	DD3D12ResourceAllocation AllocateBuffer(const TString& DebugName, EGPUBufferMutability Mutability, uint64 ByteWidth);

private:
	PCom<D3D12MA::Allocator> m_Allocator;
};