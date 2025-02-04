#pragma once

#include "Core.h"

class SCPUBlob : public SIntrusiveRefCounted
{
public:
	SCPUBlob() = default;
	~SCPUBlob();

	SCPUBlob(const SCPUBlob& Other);
	SCPUBlob& operator=(SCPUBlob& Other);

	SCPUBlob(SCPUBlob&& Other) noexcept
	{
		Swap(Other);
	}

	SCPUBlob& operator=(SCPUBlob&& Other) noexcept
	{
		Swap(Other);
		return *this;
	}

	inline void* GetBufferPointer() const { return m_Buffer; }
	inline uint64 GetBufferSize() const { return m_BufferSize; }

	inline bool IsValid() const { return m_Buffer != nullptr && m_BufferSize > 0; }
	inline operator bool() const { return IsValid(); }

private:
	void Reset() noexcept;
	void Swap(SCPUBlob& Other) noexcept;

	void AllocateBuffer(uint64 Size, const void* Data);

private:
	void* m_Buffer{};
	uint64 m_BufferSize{};

	friend SCPUBlob CreateCPUBlob(uint64 Size, const void* Data);
	friend SCPUBlob* AllocateCPUBlob(uint64 Size, const void* Data);
};


SCPUBlob CreateCPUBlob(uint64 Size, const void* Data = nullptr);
SCPUBlob* AllocateCPUBlob(uint64 Size, const void* Data = nullptr);