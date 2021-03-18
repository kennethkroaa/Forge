#pragma once

#ifdef FORGE_PLATFORM_WINDOWS

extern 
Forge::Application* Forge::CreateApplication();

int 
main(int argc, char** argv) 
{
	Forge::Log::Init();
	FORGE_CORE_WARN("Initialized sdplog");

	auto app = Forge::CreateApplication();
	app->Run();
	delete app;
}

#endif