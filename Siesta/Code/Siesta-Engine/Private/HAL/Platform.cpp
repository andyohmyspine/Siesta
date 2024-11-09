#include "HAL/Platform.h"

extern void HALDestroyPlatform(IPlatform* Platform)
{
	delete Platform;
}

IPlatform* IPlatform::This;
IPlatform::IPlatform()
{
	This = this;
}
