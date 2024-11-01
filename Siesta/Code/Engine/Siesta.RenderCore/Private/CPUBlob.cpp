#include "CPUBlob.h"

SCPUBlob::~SCPUBlob()
{
	Reset();
}

SCPUBlob::SCPUBlob(const SCPUBlob& Other)
{
	if (Other.IsValid())
	{
		AllocateBuffer(Other.m_BufferSize, Other.m_Buffer);
	}
}

SCPUBlob& SCPUBlob::operator=(SCPUBlob& Other)
{
	if (Other.IsValid())
	{
		AllocateBuffer(Other.m_BufferSize, Other.m_Buffer);
	}

	return *this;
}

void SCPUBlob::Reset() noexcept
{
	if (m_Buffer)
	{
		delete[] reinterpret_cast<uint8*>(m_Buffer);
		m_Buffer = nullptr;
	}

	m_BufferSize = 0;
}

void SCPUBlob::Swap(SCPUBlob& Other) noexcept
{
	Reset();

	m_Buffer = Other.m_Buffer;
	Other.m_Buffer = nullptr;

	m_BufferSize = Other.m_BufferSize;
	Other.m_BufferSize = 0;
}

void SCPUBlob::AllocateBuffer(uint64 Size, const void* Data)
{
	if (m_Buffer)
	{
		Reset();
	}

	m_BufferSize = Size;
	m_Buffer = new uint8[Size];

	if (Data)
	{
		memcpy(m_Buffer, Data, Size);
	}
}

SCPUBlob CreateCPUBlob(uint64 Size, const void* Data /*= nullptr*/)
{
	SCPUBlob OutBlob;
	OutBlob.AllocateBuffer(Size, Data);
	return OutBlob;
}

SCPUBlob* AllocateCPUBlob(uint64 Size, const void* Data /*= nullptr*/)
{
	SCPUBlob* Blob = new SCPUBlob();
	Blob->AllocateBuffer(Size, Data);
	return Blob;
}
