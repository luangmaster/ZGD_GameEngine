#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ZGD {

	class ZGD_API Log
	{
	public:
		Log();
		~Log();

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// core log macros
#define ZGD_CORE_TRACE(...)	::ZGD::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ZGD_CORE_INFO(...)	::ZGD::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ZGD_CORE_WARN(...)	::ZGD::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ZGD_CORE_ERROR(...)	::ZGD::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ZGD_CORE_FATAL(...)	::ZGD::Log::GetCoreLogger()->critical(__VA_ARGS__)

// client log macros
#define ZGD_TRACE(...)	::ZGD::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ZGD_INFO(...)	::ZGD::Log::GetClientLogger()->info(__VA_ARGS__)
#define ZGD_WARN(...)	::ZGD::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ZGD_ERROR(...)	::ZGD::Log::GetClientLogger()->error(__VA_ARGS__)
#define ZGD_FATAL(...)	::ZGD::Log::GetClientLogger()->critical(__VA_ARGS__)

