#pragma once

#ifdef GA_PLATFORM_WINDOWS
	#ifdef GA_BUILD_DLL
		#define GAEA_API __declspec(dllexport)
	#else
		#define GAEA_API __declspec(dllimport)
	#endif
#else
	#error Gaea only supports Windows!
#endif

#ifdef GA_ENABLE_ASSERTS 
	#define GA_ASSERT(x, ...) { if(!(x)) { GA_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GA_CORE_ASSERT(x, ...) { if(!(x)) { GA_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GA_ASSERT(x, ...)
	#define GA_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

#define GA_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1))