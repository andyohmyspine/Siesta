#pragma once

#include "Types.h"
#include "Async.h"
#include "FileSystem.h"
#include "Logging.h"
#include "ModuleManager.h"
#include "Math/DMath.h"
#include "Delegate.h"
#include "IntrusiveRefCounted.h"

template<typename ... Args>
inline constexpr TString FormatString(fmt::format_string<Args...> Format, Args&&... InArgs)
{
	return fmt::format(Format, std::forward<Args>(InArgs)...);
}

class TSiestaCore
{
public:
	TSiestaCore();
	~TSiestaCore();
};

