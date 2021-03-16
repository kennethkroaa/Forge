#pragma once

#include "Core.h"

namespace Forge {
	class FORGE_API 
	Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client
	Application* CreateApplication();
}


