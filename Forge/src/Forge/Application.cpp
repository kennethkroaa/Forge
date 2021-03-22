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

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		layerStack.PushOverlay(overlay);
	}

	void Application::onEvent(Event& event) 
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		FORGE_CORE_TRACE("{0}", event);

		// Go backward in layer stack
		// Required as overlays are last, and we want e.g. GUI to receive events first
		for (auto it = layerStack.end(); it != layerStack.begin(); )
		{
			(*--it)->onEvent(event);
			if (event.handled)
				break;
		}
	}

	void 
	Application::run() 
	{
		while (running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window->onUpdate();

			for (Layer* layer : layerStack)
				layer->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		running = false;
		return true;
	}
}