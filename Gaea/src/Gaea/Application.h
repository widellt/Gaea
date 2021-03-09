#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Gaea/Events/ApplicationEvent.h"

#include "Window.h"


namespace Gaea {
	class GAEA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> _Window;
		bool _Running = true;
	};

	// To be defined in Client
	Application* CreateApplication();
}


