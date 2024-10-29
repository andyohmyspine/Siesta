#include "SiestaLogging.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#ifdef _MSC_VER
#include <spdlog/sinks/msvc_sink.h>
#endif

PSharedPtr<TLogger> SLogManager::GetLogger()
{
	if (!m_Logger)
	{
		CreateLogger();
	}

	return m_Logger;
}

void SLogManager::CreateLogger()
{
	// Sinks
	PDynArray<TLogSinkPtr> Sinks
	{
		MakeShared<spdlog::sinks::stdout_color_sink_mt>(),
		MakeShared<spdlog::sinks::basic_file_sink_mt>("Logs/Log.txt"),

	#ifdef _MSC_VER
		MakeShared<spdlog::sinks::msvc_sink_mt>()
	#endif
	};

	m_Logger = MakeShared<TLogger>(TString("Siesta Log"));
	const auto LogPattern = "%^[%H:%M:%S](%l): %v%$";
	for (auto& Sink : Sinks)
	{
		Sink->set_level(spdlog::level::trace);
		Sink->set_pattern(LogPattern);

		m_Logger->sinks().push_back(Sink);
	}

	m_Logger->set_level(spdlog::level::trace);
	m_Logger->set_pattern(LogPattern);
}

PSharedPtr<TLogger> SLogManager::m_Logger;
