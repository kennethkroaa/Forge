#pragma once

#include "Core.h"

#include "Window.h"
#include <Forge/LayerStack.h>
#include "Events/Event.h"
#include "Forge/Events/ApplicationEvent.h"

namespace 
Forge 
{
	class FORGE_API 
	Application 
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool onWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> window;
		bool running = true;
		LayerStack layerStack;
	};

	//To be defined in client
	Application* createApplication();
}


