#pragma once
#include "CoreAPI.h"

#include "SiestaTypes.h"

#include <spdlog/spdlog.h>

using TLogger = spdlog::logger;
using TLogSink = spdlog::sinks::sink;
using TLogSinkPtr = PSharedPtr<TLogSink>;

class CORE_API SLogManager
{
public:
	static PSharedPtr<TLogger> GetLogger();

private:
	static void CreateLogger();
	static PSharedPtr<TLogger> m_Logger;
};

#ifdef _MSC_VER
	#define SIESTA_BREAK() __debugbreak()
#else
	#define SIESTA_BREAK()
#endif

namespace Debug
{
	template<typename ... Args>
	inline void Trace(fmt::format_string<Args...> Format, Args&&... InArgs) { SLogManager::GetLogger()->trace(Format, std::forward<Args>(InArgs)...); }

	template<typename ... Args>
	inline void Debug(fmt::format_string<Args...> Format, Args&&... InArgs) { SLogManager::GetLogger()->debug(Format, std::forward<Args>(InArgs)...); }

	template<typename ... Args>
	inline void Info(fmt::format_string<Args...> Format, Args&&... InArgs) { SLogManager::GetLogger()->info(Format, std::forward<Args>(InArgs)...); }

	template<typename ... Args>
	inline void Warning(fmt::format_string<Args...> Format, Args&&... InArgs) { SLogManager::GetLogger()->warn(Format, std::forward<Args>(InArgs)...); }

	template<typename ... Args>
	inline void Error(fmt::format_string<Args...> Format, Args&&... InArgs) { SLogManager::GetLogger()->error(Format, std::forward<Args>(InArgs)...); }

	template<typename ... Args>
	inline void Critical(fmt::format_string<Args...> Format, Args&&... InArgs) 
	{ 
		SLogManager::GetLogger()->critical(Format, std::forward<Args>(InArgs)...); 
		SIESTA_BREAK();
		throw TRuntimeError(fmt::format(Format, std::forward<Args>(InArgs)...));
	}
}