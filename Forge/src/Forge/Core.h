#pragma once

#ifdef FORGE_PLATFORM_WINDOWS
	#ifdef FORGE_BUILD_DLL
		#define FORGE_API __declspec(dllexport)
	#else
		#define FORGE_API __declspec(dllimport)
	#endif
#else
	#error Forge only supports Windows!
#endif