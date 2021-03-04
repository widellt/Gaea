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