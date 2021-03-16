#pragma once

#include <memory.h>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace 
Forge 
{
	class FORGE_API
	Log 
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core logger macros
#define FORGE_CORE_TRACE(...)	::Forge::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FORGE_CORE_INFO(...)	::Forge::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FORGE_CORE_WARN(...)	::Forge::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FORGE_CORE_ERROR(...)	::Forge::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FORGE_CORE_FATAL(...)	::Forge::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client logger macros
#define FORGE_TRACE(...)		::Forge::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FORGE_INFO(...)			::Forge::Log::GetClientLogger()->info(__VA_ARGS__)
#define FORGE_WARN(...)			::Forge::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FORGE_ERROR(...)		::Forge::Log::GetClientLogger()->error(__VA_ARGS__)
#define FORGE_FATAL(...)		::Forge::Log::GetClientLogger()->fatal(__VA_ARGS__)