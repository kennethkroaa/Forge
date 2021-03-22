#include "forgepch.h"
#include "Application.h"

#include "Forge/Log.h"
#include <gl/GL.h>

namespace 
Forge 
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() 
	{
		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(BIND_EVENT_FN(onEvent));
	}

	Application::~Application() 
	{

	}

	void Application::onEvent(Event& event) 
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		FORGE_CORE_TRACE("{0}", event);
	}

	void 
	Application::run() 
	{
		while (running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		running = false;
		return true;
	}
}