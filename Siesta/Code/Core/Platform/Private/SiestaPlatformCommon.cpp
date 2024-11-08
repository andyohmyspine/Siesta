#pragma once

#include "Interfaces/IPlatform.h"

#ifdef SIESTA_USE_GLFW
#include "SiestaPlatformGLFW.cpp.inl"
#endif

IPlatformInterface* IPlatformInterface::This;

IPlatformInterface::IPlatformInterface()
{
	This = this;
}

IPlatformInterface& IPlatformInterface::Get()
{
	return *This;
}