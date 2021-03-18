#include <Forge.h>

class Sandbox : public Forge::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Forge::Application* Forge::createApplication() {
	return new Sandbox();
}