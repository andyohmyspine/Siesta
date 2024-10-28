#pragma once

#include "SiestaCore.h"
#include "Siesta.PlatformCommonAPI.h"

class SIESTA_PLATFORMCOMMON_API IPlatformWindow
{
public:
	virtual void* GetNativeHandle() const = 0;

	virtual Math::XMINT2 GetWindowSize() const = 0;

protected:
	virtual ~IPlatformWindow() = default;
};