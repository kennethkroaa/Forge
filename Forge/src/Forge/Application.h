#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Forge/Events/ApplicationEvent.h"

#include "Window.h"

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
	private:
		bool onWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> window;
		bool running = true;
	};

	//To be defined in client
	Application* createApplication();
}


