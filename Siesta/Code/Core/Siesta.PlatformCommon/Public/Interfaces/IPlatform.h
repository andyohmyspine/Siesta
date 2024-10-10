#pragma once

#include "Siesta.PlatformCommonAPI.h"

class SIESTA_PLATFORMCOMMON_API IPlatformInterface
{
	static IPlatformInterface* This;

public:
	virtual ~IPlatformInterface() = default;

	static IPlatformInterface& Get();

protected:
	IPlatformInterface();
};