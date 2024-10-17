#pragma once

#include "Siesta.PlatformCommonAPI.h"

class IPlatformWindow;

class SIESTA_PLATFORMCOMMON_API IPlatformInterface
{
	static IPlatformInterface* This;

public:
	virtual ~IPlatformInterface() = default;

	static IPlatformInterface& Get();
	static IPlatformInterface* Create();

	virtual IPlatformWindow* CreatePlatformWindow(int32 Width, int32 Height, TStringView Title) = 0;
	virtual bool ShouldExit() const = 0;
	virtual void Process() = 0;

protected:
	IPlatformInterface();
};