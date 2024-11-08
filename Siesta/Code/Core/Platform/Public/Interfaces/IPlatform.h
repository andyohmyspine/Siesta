#pragma once

#include "SiestaCore.h"
#include "PlatformAPI.h"

class IPlatformWindow;

MAKE_MULTIDELEGATE_TYPE(DOnWindowResized, const IPlatformWindow*, int32, int32);

class PLATFORM_API IPlatformInterface
{
	static IPlatformInterface* This;

public:
	virtual ~IPlatformInterface() = default;

	static IPlatformInterface& Get();
	static IPlatformInterface* Create();

	virtual IPlatformWindow* CreatePlatformWindow(int32 Width, int32 Height, TStringView Title) = 0;
	virtual bool ShouldExit() const = 0;
	virtual void Process() = 0;

	DOnWindowResized OnWindowResizedCallback;

	virtual IPlatformWindow* GetMainWindow() const = 0;

protected:
	IPlatformInterface();
};