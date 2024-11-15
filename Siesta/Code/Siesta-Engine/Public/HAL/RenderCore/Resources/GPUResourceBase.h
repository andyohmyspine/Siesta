#pragma once

#include "Core.h"

enum class EGPUResourceType
{
	Buffer,
	Texture,
};

class SGPUResourceBase : public SIntrusiveRefCounted
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