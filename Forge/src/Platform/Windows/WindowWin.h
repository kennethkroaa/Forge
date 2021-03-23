#pragma once

#include "Window.h"

#include <GLFW/glfw3.h>

namespace
Forge
{
	class WindowWin : public Window
	{
	public:
		WindowWin(const WindowProps& props);
		virtual ~WindowWin();

		void onUpdate() override;

		inline unsigned int getHeight() const override { return data.width; }
		inline unsigned int getWidth() const override { return data.height; }

		//Window attributes
		inline void setEventCallback(const eventCallbackFn& callback) override { data.eventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;

		virtual void* getNativeWindow() const { return window; }
	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();
	private:
		GLFWwindow* window;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;

			eventCallbackFn eventCallback;
		};

		WindowData data;
	};
}