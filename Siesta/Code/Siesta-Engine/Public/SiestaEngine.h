#pragma once

#include "SiestaCore.h"

// Platform helpers to forward declare some stuff we don't need on client
class IPlatform;
class IPlatformWindow;
extern void HALDestroyPlatform(IPlatform* Platform);
namespace Detail
{
	const auto IPlatform_Deleter = [](IPlatform* Platform) { HALDestroyPlatform(Platform); };
}

class SEngine
{
public:
	SEngine();
	virtual ~SEngine();

	virtual void Run();

private:
	PUniquePtr<IPlatform, decltype(Detail::IPlatform_Deleter)> m_Platform;
	IPlatformWindow* m_MainWindow{};
};

extern SEngine* CreateEngine();

#ifdef SIESTA_MAIN
	#include "SiestaMain.inl"
#endif