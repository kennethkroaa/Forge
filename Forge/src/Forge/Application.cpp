#include "forgepch.h"
#include "Application.h"

#include "Forge/Events/ApplicationEvent.h"
#include "Forge/Log.h"

namespace 
Forge 
{
	Application::Application() 
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() 
	{

	}

	void 
	Application::Run() 
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}