#pragma once

#include "CoreAll.h"
#include "RenderCoreAPI.h"
#include "SiestaIntrusivePtr.h"

enum class EGPUResourceType
{
	Buffer,
	Texture,
};

class RENDERCORE_API SGPUResourceBase : public SIntrusiveRefCounted
{
public:
	SGPUResourceBase() = default;
	SGPUResourceBase(const TString& Name, EGPUResourceType Type);
	virtual ~SGPUResourceBase() = default;

	inline TStringView GetName() const { return m_Name; }
	inline EGPUResourceType GetType() const { return m_Type; }

private:
	TString m_Name {};
	EGPUResourceType m_Type {};
};