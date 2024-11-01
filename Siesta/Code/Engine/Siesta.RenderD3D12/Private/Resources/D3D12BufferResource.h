#pragma once

#include "D3D12Common.h"
#include "Resources/GPUBufferResource.h"
#include "Siesta.RenderD3D12API.h"
#include "D3D12ResourceAllocator.h"

class SCPUBlob;

class SIESTA_RENDERD3D12_API SD3D12BufferResource : public SGPUBufferResource
{
public:
	SD3D12BufferResource(const DGPUBufferDesc& Desc);

	virtual void WriteData(const void* Data, uint64 DataSize, uint64 ByteOffset) override;
	inline bool IsCPUMemoryDirty() const { return m_IsAwaitingGPUTransfer; }

	inline void MarkCPUMemoryDirty(bool Dirty)
	{
		m_IsAwaitingGPUTransfer = Dirty;
	}

	inline ID3D12Resource* GetResource() const { return m_Allocation.Resource.Get(); }

	void SetUsableOnFrame(uint64 FrameIndex);

	inline bool IsUsable() const
	{
		if (m_Desc.Mutability != EGPUBufferMutability::Static)
			return true;

		return !IsCPUMemoryDirty() || (m_UsableOnFrame == UINT64_MAX || GCurrentFrameIndex >= m_UsableOnFrame);
	}

private:
	DD3D12ResourceAllocation m_Allocation;
	uint64 m_UsableOnFrame = UINT64_MAX;

	SCPUBlob* m_CPUData;
	void* m_MappedResourceData;

	bool m_IsAwaitingGPUTransfer:1 = false;
	friend class SD3D12RenderContext;
};