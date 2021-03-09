#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Gaea/Events/ApplicationEvent.h"




namespace Gaea {
	class GAEA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> _Window;
		bool _Running = true;
		LayerStack _LayerStack;
	};

	// To be defined in Client
	Application* CreateApplication();
}


