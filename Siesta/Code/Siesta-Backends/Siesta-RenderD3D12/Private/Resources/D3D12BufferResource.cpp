#include "HAL/RenderCore/CPUBlob.h"
#include "HAL/RenderCore/BufferUtils.h"

#include "D3D12BufferResource.h"
#include "D3D12RenderDevice.h"

SD3D12BufferResource::SD3D12BufferResource(const DGPUBufferDesc& Desc)
	: SGPUBufferResource(Desc)
{
	m_Allocation = SD3D12ResourceAllocator::Get().AllocateBuffer(Desc.DebugName, Desc.Mutability, Desc.ByteSize);

	if (Desc.Mutability == EGPUBufferMutability::Static)
	{
		m_CPUData = AllocateCPUBlob(Desc.ByteSize);
	}
	else if (Desc.Mutability == EGPUBufferMutability::Dynamic || Desc.Mutability == EGPUBufferMutability::Staging)
	{
		m_Allocation.Resource->Map(0, nullptr, &m_MappedResourceData);
	}
}

void SD3D12BufferResource::WriteData(const void* Data, uint64 DataSize, uint64 ByteOffset)
{
	if (m_Desc.Mutability == EGPUBufferMutability::Static)
	{
		if (m_CPUData && m_CPUData->IsValid())
		{
			memcpy((uint8*)m_CPUData->GetBufferPointer() + ByteOffset, Data, DataSize);
			MarkCPUMemoryDirty(true);

			DPendingBufferTransfer Transfer{};
			Transfer.DstResource = this;
			Transfer.InitialState = D3D12_RESOURCE_STATE_COMMON;
			Transfer.FinalState = D3D12_RESOURCE_STATE_GENERIC_READ;

			EnqueueBufferTransfer(Transfer);
		}
	}
	else
	{
		if (m_MappedResourceData)
		{
			memcpy((uint8*)m_MappedResourceData + ByteOffset, Data, DataSize);
		}
	}
}

void SD3D12BufferResource::SetUsableOnFrame(uint64 FrameIndex)
{
	m_UsableOnFrame = FrameIndex;
}
