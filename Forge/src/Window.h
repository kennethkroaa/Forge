#pragma once

#include "forgepch.h"

#include "Forge/Core.h"
#include "Forge/Events/event.h"

namespace
Forge
{
	struct 
	WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(
			const std::string& title = "Forge Engine",
			unsigned int width = 1280,
			unsigned int height = 720
		): title(title), width(width), height(height) {}
	};

	//Interface representing a desktop system based Window
	//To be implemented on a per-platform basis
	class FORGE_API
	Window
	{
	public:
		using eventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		//Window attributes
		virtual void setEventCallback(const eventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Window* create(const WindowProps& props = WindowProps());
	};
}