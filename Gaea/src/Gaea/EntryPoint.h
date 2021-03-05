#pragma once

#ifdef GA_PLATFORM_WINDOWS

extern Gaea::Application* Gaea::CreateApplication();

int main(int argc, char** argv) {
	Gaea::Log::Init();
	GA_CORE_WARN("Init Log");
	int a = 5;
	GA_INFO("Hello! Var{0}", a);
	auto app = Gaea::CreateApplication();
	// Entry point of application
	app->Run();
	delete app;
	return 0;
}

#endif
