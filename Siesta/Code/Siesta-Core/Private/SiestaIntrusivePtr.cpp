#include "SiestaIntrusivePtr.h"

uint64 SIntrusiveRefCounted::AddRef() const
{
	m_RefCount++;
	return m_RefCount;
}

uint64 SIntrusiveRefCounted::GetRefCount() const
{
	return m_RefCount;
}

uint64 SIntrusiveRefCounted::Release() const
{
	m_RefCount--;
	if (m_RefCount == 0)
	{
		delete this;
		return 0;
	}

	return m_RefCount;
}

extern uint64 Detail::AddRef_RefCounted(const void* Ptr)
{
	if (const SIntrusiveRefCounted* RefPtr = static_cast<const SIntrusiveRefCounted*>(Ptr))
	{
		return RefPtr->AddRef();
	}

	return 0;
}

extern uint64 Detail::ReleaseRef_RefCounted(const void* Ptr)
{
	if (const SIntrusiveRefCounted* RefPtr = static_cast<const SIntrusiveRefCounted*>(Ptr))
	{
		return RefPtr->Release();
	}

	return 0;
}
