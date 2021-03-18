#include "forgepch.h"
#include "WindowWin.h"

namespace
Forge
{
	static bool GLFWInitialized = false;

	Window*
	Window::create(const WindowProps& props)
	{
		return new WindowWin(props);
	}

	WindowWin::WindowWin(const WindowProps& props)
	{
		init(props);
	}

	WindowWin::~WindowWin()
	{
		shutdown();
	}

	void
	WindowWin::init(const WindowProps& props)
	{
		data.title = props.title;
		data.width = props.width;
		data.height = props.height;

		FORGE_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!GLFWInitialized)
		{
			int success = glfwInit();
			FORGE_CORE_ASSERT(success, "Could not initialize GLFW!")

			GLFWInitialized = true;
		}

		window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		setVSync(true);
	}

	void
	WindowWin::shutdown()
	{
		glfwDestroyWindow(window);
	}

	void
	WindowWin::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void
	WindowWin::setVSync(bool enabled)
	{
		glfwSwapInterval(int(enabled));
		data.vSync = enabled;
	}

	bool
	WindowWin::isVSync() const
	{
		return data.vSync;
	}
}