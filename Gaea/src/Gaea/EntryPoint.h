#pragma once

#ifdef GA_PLATFORM_WINDOWS

extern Gaea::Application* Gaea::CreateApplication();

int main(int argc, char** argv) {
	auto app = Gaea::CreateApplication();
	// Entry point of application
	app->Run();
	delete app;
	return 0;
}

#endif
