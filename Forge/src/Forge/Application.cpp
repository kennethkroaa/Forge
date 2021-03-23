#include "forgepch.h"
#include "Application.h"

#include "Forge/Log.h"
#include <glad/gl.h>

namespace 
Forge 
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;

	Application::Application() 
	{
		FORGE_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(BIND_EVENT_FN(onEvent));
	}

	Application::~Application() 
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
		layer->onAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		layerStack.PushOverlay(overlay);
		overlay->onAttach();
	}

	void Application::onEvent(Event& event) 
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

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