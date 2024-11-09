#pragma once

#include "SiestaCore.h"

class IPlatformWindow
{
public:
	virtual ~IPlatformWindow() = default;
	virtual void* GetNativeHandle() const = 0;
	virtual Math::XMINT2 GetWindowSize() const = 0;
};

MAKE_MULTIDELEGATE_TYPE(DOnWindowResized, const IPlatformWindow*, int32, int32);
class IPlatform
{
	static IPlatform* This;

public:
	virtual ~IPlatform() = default;

	static IPlatform& Get() { return *This; }

	virtual IPlatformWindow* CreatePlatformWindow(int32 Width, int32 Height, TStringView Title) = 0;
	virtual bool ShouldExit() const = 0;
	virtual void Process() = 0;

	DOnWindowResized OnWindowResizedCallback;

	virtual IPlatformWindow* GetMainWindow() const = 0;

protected:
	IPlatform();
};

extern IPlatform* HALCreatePlatform();

void HALDestroyPlatform(IPlatform* Platform);