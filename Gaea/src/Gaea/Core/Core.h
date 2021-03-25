#pragma once

#include <memory>


// Platform detection using predefined macros
#ifdef _WIN32
	/*Windows x86/x64 */
	#ifdef _WIN64
		#define	GA_PLATFORM_WINDOWS

	#else 
		#error "x86 Builds are not supported!"
	#endif
	
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>

	/* 
	TARGET_OS_MAC exists on all
	platforms so we need to check all of them
	in order to ensure that we're running on Mac
	and not on another Apple platform*
	*/
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS Simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define GA_PLATFORM_IOS
		#error "IOS Simulator is not supported!"
	#elif TARGET_OS_MAC == 1
		#define GA_PLATFORM_MACOS
		#error "IOS Simulator is not supported!"
	#else
		#error "Uknown Apple platform!"
	#endif
	/*
	We also have to check Android before linux, since 
	Android is based on the linux kernel __linux__ will 
	already be defined
	*/
#elif defined(__ANDROID__)
	#define GA_PLATFORM_ANDROID
	#error "Android not supported!"
#elif defined(__ANDROID__)
	#define GA_PLATFORM_LINUX
	#error "Linux not supported!"
#else
	#error "Uknown platform!"
#endif

#ifdef GA_PLATFORM_WINDOWS
	#if DYNAMIC_LINK
		#ifdef GA_BUILD_DLL
			#define GAEA_API __declspec(export)
		#else
			#define GAEA_API __declspec(import)
		#endif
	#else
		#define GAEA_API 
	#endif
#else
	#error "Gaea only supports Windows!"
#endif // GA_BUILD_DLL, end of support


#ifdef GA_DEBUG
	#define GA_ENABLE_ASSERTS
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

namespace Gaea {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}