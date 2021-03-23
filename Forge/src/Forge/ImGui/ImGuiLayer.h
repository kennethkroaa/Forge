#pragma once

#include "Forge/Layer.h"

namespace
Forge
{
	class FORGE_API
	ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& event);
	private:
		float currentTime = 0.0f;
	};
}