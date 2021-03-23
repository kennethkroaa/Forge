#include "forgepch.h"
#include "WindowWin.h"

#include <Forge/Events/ApplicationEvent.h>
#include <Forge/Events/MouseEvent.h>
#include <Forge/Events/KeyEvent.h>

#include <glad/gl.h>

namespace
Forge
{
	static bool GLFWInitialized = false;

	static void 
	GLFWErrorCallback(int error, const char* description)
	{
		FORGE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
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
			glfwSetErrorCallback(GLFWErrorCallback);

			GLFWInitialized = true;
		}

		window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		int version = gladLoadGL(glfwGetProcAddress);
		FORGE_CORE_ASSERT(version, "Failed to initialize glad");
		FORGE_CORE_WARN("Loaded OpenGL {0}.{1}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
		glfwSetWindowUserPointer(window, &data);
		setVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.eventCallback(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.eventCallback(event);
		});
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