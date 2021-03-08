#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <memory>

namespace Gaea {

	class GAEA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define GA_CORE_TRACE(...)		::Gaea::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GA_CORE_INFO(...)		::Gaea::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GA_CORE_WARN(...)		::Gaea::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GA_CORE_ERROR(...)		::Gaea::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GA_CORE_FATAL(...)		::Gaea::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define GA_TRACE(...)			::Gaea::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GA_INFO(...)			::Gaea::Log::GetClientLogger()->info(__VA_ARGS__)
#define GA_WARN(...)			::Gaea::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GA_ERROR(...)			::Gaea::Log::GetClientLogger()->error(__VA_ARGS__)
#define GA_FATAL(...)			::Gaea::Log::GetClientLogger()->fatal(__VA_ARGS__)