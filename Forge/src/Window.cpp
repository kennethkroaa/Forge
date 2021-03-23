#include "forgepch.h"
#include "Window.h"

#ifdef FORGE_PLATFORM_WINDOWS
#include "Platform/Windows/WindowWin.h"
#endif

namespace Forge
{
	Scope<Window> Window::create(const WindowProps& props)
	{
		#ifdef FORGE_PLATFORM_WINDOWS
			return CreateScope<WindowWin>(props);
		#else
			FORGE_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}