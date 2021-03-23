#pragma once

#include <memory>

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

namespace Forge {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}