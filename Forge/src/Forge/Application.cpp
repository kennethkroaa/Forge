#include "Application.h"

#include "Forge/Events/ApplicationEvent.h"
#include "Forge/Log.h"

namespace 
Forge 
{
	Application::Application() 
	{

	}

	Application::~Application() 
	{

	}

	void 
	Application::Run() 
	{
		WindowResizeEvent e(1280, 720);
		FORGE_TRACE(e);

		while (true);
	}
}