#pragma once

#include "Types.h"

#include <atomic>

class SIntrusiveRefCounted
{
public:
	SIntrusiveRefCounted() = default;
	virtual ~SIntrusiveRefCounted() = default;

	uint64 AddRef() const;
	uint64 GetRefCount() const;
	uint64 Release() const;

private:
	mutable std::atomic_uint64_t m_RefCount = 1;
};

namespace Detail
{
	extern uint64 AddRef_RefCounted(const void* Ptr);
	extern uint64 ReleaseRef_RefCounted(const void* Ptr);
}

// Need to allow for forward decl
template<typename T>
class PRefCntPtr
{
public:
	PRefCntPtr(TTypeOfNull)
		: m_RefCounted(nullptr)
	{
	}

	PRefCntPtr()
		: PRefCntPtr((TTypeOfNull)nullptr)
	{
	}

	PRefCntPtr(T* Value)
		: m_RefCounted(Value)
	{
	}

	~PRefCntPtr()
	{
		if (m_RefCounted != nullptr)
		{
			Detail::ReleaseRef_RefCounted(m_RefCounted);
		}
	}

	PRefCntPtr& operator=(T* Value)
	{
		if (m_RefCounted)
		{
			Detail::ReleaseRef_RefCounted(m_RefCounted);
		}

		m_RefCounted = Value;
		return *this;
	}

private:
	SIntrusiveRefCounted* m_RefCounted {};
};