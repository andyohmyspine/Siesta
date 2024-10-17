#pragma once

#include "SiestaCore.h"
#include "Siesta.PlatformCommonAPI.h"

struct DWindowBounds
{
	int32 Width;
	int32 Height;
};

class SIESTA_PLATFORMCOMMON_API IPlatformWindow
{
public:
	virtual DWindowBounds GetWindowBounds() const = 0;

	virtual void* GetNativeHandle() const = 0;

protected:
	virtual ~IPlatformWindow() = default;
};