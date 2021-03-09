#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Gaea {
	class GAEA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> _Window;
		bool _Running = true;
	};

	// To be defined in Client
	Application* CreateApplication();
}


