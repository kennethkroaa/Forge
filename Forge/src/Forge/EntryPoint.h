#pragma once

#ifdef FORGE_PLATFORM_WINDOWS

extern 
Forge::Application* Forge::CreateApplication();

int 
main(int argc, char** argv) 
{
	Forge::Log::Init();
	FORGE_CORE_WARN("Initialized log!");

	int a = 5;
	FORGE_INFO("Hello! Var={0}", a);

	auto app = Forge::CreateApplication();
	app->Run();
	delete app;
}

#endif