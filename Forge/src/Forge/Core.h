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

#ifdef FORGE_ENABLE_ASSERTS
	#define FORGE_ASSERT(x, ...) { if(!(x)) { FORGE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FORGE_CORE_ASSERT(x, ...) { if(!(x)) { FORGE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FORGE_ASSERT(x, ...)
	#define FORGE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)