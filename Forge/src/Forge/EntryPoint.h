#pragma once

#ifdef FORGE_PLATFORM_WINDOWS

extern 
Forge::Application* Forge::createApplication();

int 
main(int argc, char** argv) 
{
	Forge::Log::init();
	FORGE_CORE_WARN("Initialized sdplog");

	auto app = Forge::createApplication();
	app->run();
	delete app;
}

#endif