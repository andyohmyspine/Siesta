#pragma once

#include "D3D12Common.h"
#include "D3D12ResourceAllocator.h"

#include "HAL/RenderCore/Resources/GPUBufferResource.h"

class SCPUBlob;

class SD3D12BufferResource : public SGPUBufferResource
{
public:
	SD3D12BufferResource(const DGPUBufferDesc& Desc);

	virtual void WriteData(const void* Data, uint64 DataSize, uint64 ByteOffset) override;
	inline bool IsCPUMemoryDirty() const { return m_IsCPUMemoryDirty; }

	inline void MarkCPUMemoryDirty(bool Dirty)
	{
		m_IsCPUMemoryDirty = Dirty;
	}

	inline ID3D12Resource* GetResource() const { return m_Allocation.Resource.Get(); }

	void SetUsableOnFrame(uint64 FrameIndex);

	inline bool IsUsable() const
	{
		return !IsCPUMemoryDirty();
	}

private:
	DD3D12ResourceAllocation m_Allocation;
	uint64 m_UsableOnFrame = UINT64_MAX;

	SCPUBlob* m_CPUData;
	void* m_MappedResourceData;

	bool m_IsCPUMemoryDirty:1 = false;
	friend class SD3D12RenderContext;
};