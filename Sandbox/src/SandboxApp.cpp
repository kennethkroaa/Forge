#include <Forge.h>

class 
ExampleLayer : public Forge::Layer
{
public:
	ExampleLayer(): Layer("Example") {}

	void onUpdate() override
	{
		FORGE_INFO("ExampleLayer::Update");
	}

	void onEvent(Forge::Event& event) override
	{
		FORGE_TRACE("{0}", event);
	}
};

class Sandbox : public Forge::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Forge::Application* Forge::createApplication() {
	return new Sandbox();
}