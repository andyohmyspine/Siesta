#pragma once

#include "GPUResourceBase.h"

enum class EGPUBufferMutability
{
	Static,
	Dynamic,
	Staging,
	Readback,
};

enum EGPUBufferUsage : uint16
{
	BU_None = 0,
	BU_Vertex = 1 << 0,
	BU_Index = 1 << 1,
	BU_ShaderResource = 1 << 2,
	BU_UnorderedAccess = 1 << 3,
};
using TBufferUsageMask = uint16;

struct DGPUBufferDesc
{
	TString DebugName;
	uint64 ByteSize;
	uint64 ByteStride;
	EGPUBufferMutability Mutability;
	TBufferUsageMask Usage;
};

class SIESTA_RENDERCORE_API SGPUBufferResource : public SGPUResourceBase
{
public:
	SGPUBufferResource(const DGPUBufferDesc& Desc)
		: SGPUResourceBase(Desc.DebugName, EGPUResourceType::Buffer)
		, m_Desc(Desc)
	{
	}

	virtual void WriteData(const void* Data, uint64 DataSize, uint64 ByteOffset) = 0;

	inline const DGPUBufferDesc& GetDesc() const { return m_Desc; }

protected:
	DGPUBufferDesc m_Desc {};
};