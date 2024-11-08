#pragma once

#include "SiestaCore.h"
#include "PlatformAPI.h"

class PLATFORM_API IPlatformWindow
{
public:
	virtual void* GetNativeHandle() const = 0;

	virtual Math::XMINT2 GetWindowSize() const = 0;

protected:
	virtual ~IPlatformWindow() = default;
};