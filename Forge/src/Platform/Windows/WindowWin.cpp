#include "forgepch.h"
#include "WindowWin.h"

namespace
Forge
{
	static bool s_GLFWInitialized = false;

	Window*
	Window::Create(const WindowProps& props)
	{
		return new WindowWin(props);
	}

	WindowWin::WindowWin(const WindowProps& props)
	{
		Init(props);
	}

	WindowWin::~WindowWin()
	{
		Shutdown();
	}

	void
	WindowWin::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		FORGE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			FORGE_CORE_ASSERT(success, "Could not initialize GLFW!")

				s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void
	WindowWin::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void
	WindowWin::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void
	WindowWin::SetVSync(bool enabled)
	{
		glfwSwapInterval(int(enabled));
		m_Data.VSync = enabled;
	}

	bool
	WindowWin::IsVSync() const
	{
		return m_Data.VSync;
	}
}