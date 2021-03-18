#pragma once

#include "Core.h"
#include "Events/Event.h"
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
	private:
		std::unique_ptr<Window> window;
		bool running = true;
	};

	//To be defined in client
	Application* createApplication();
}


