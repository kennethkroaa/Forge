#pragma once

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
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

//Core logger macros
#define FORGE_CORE_TRACE(...)	::Forge::Log::getCoreLogger()->trace(__VA_ARGS__)
#define FORGE_CORE_INFO(...)	::Forge::Log::getCoreLogger()->info(__VA_ARGS__)
#define FORGE_CORE_WARN(...)	::Forge::Log::getCoreLogger()->warn(__VA_ARGS__)
#define FORGE_CORE_ERROR(...)	::Forge::Log::getCoreLogger()->error(__VA_ARGS__)
#define FORGE_CORE_FATAL(...)	::Forge::Log::getCoreLogger()->fatal(__VA_ARGS__)

//Client logger macros
#define FORGE_TRACE(...)		::Forge::Log::getClientLogger()->trace(__VA_ARGS__)
#define FORGE_INFO(...)			::Forge::Log::getClientLogger()->info(__VA_ARGS__)
#define FORGE_WARN(...)			::Forge::Log::getClientLogger()->warn(__VA_ARGS__)
#define FORGE_ERROR(...)		::Forge::Log::getClientLogger()->error(__VA_ARGS__)
#define FORGE_FATAL(...)		::Forge::Log::getClientLogger()->fatal(__VA_ARGS__)