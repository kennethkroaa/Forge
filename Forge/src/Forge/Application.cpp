#include "forgepch.h"
#include "Application.h"

#include "Forge/Events/ApplicationEvent.h"
#include "Forge/Log.h"

namespace 
Forge 
{
	Application::Application() 
	{
		window = std::unique_ptr<Window>(Window::create());
	}

	Application::~Application() 
	{

	}

	void 
	Application::run() 
	{
		while (running)
		{
			window->onUpdate();
		}
	}
}