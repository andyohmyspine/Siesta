#pragma once

#include "CoreAPI.h"

#include "SiestaTypes.h"
#include "SiestaAsync.h"
#include "SiestaFilesystem.h"
#include "SiestaLogging.h"
#include "SiestaModuleManager.h"
#include "Math/DMath.h"
#include "SiestaDelegate.h"
#include "SiestaIntrusivePtr.h"

template<typename ... Args>
inline constexpr TString FormatString(fmt::format_string<Args...> Format, Args&&... InArgs)
{
	return fmt::format(Format, std::forward<Args>(InArgs)...);
}

class TSiestaCore
{
public:
	CORE_API TSiestaCore();
	CORE_API ~TSiestaCore();
};