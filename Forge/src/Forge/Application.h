#pragma once

#include "Core.h"

#include "Window.h"
#include <Forge/LayerStack.h>
#include "Events/Event.h"
#include "Forge/Events/ApplicationEvent.h"

#include "Forge/ImGui/ImGuiLayer.h"

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

		Window& getWindow() { return *window; }

		inline static Application& get() { return *instance; }
	private:
		bool onWindowClose(WindowCloseEvent& event);

		Scope<Window> window;
		bool running = true;
		LayerStack layerStack;
		ImGuiLayer* ImGuiOverlay;
	private:
		static Application* instance;
	};

	//To be defined in client
	Application* createApplication();
}


