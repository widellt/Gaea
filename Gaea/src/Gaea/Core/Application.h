#pragma once

#include "Core.h"

#include "Window.h"
#include "Gaea/Core/LayerStack.h"
#include "Gaea/Events/Event.h"
#include "Gaea/Events/ApplicationEvent.h"

#include "Gaea/ImGui/ImGuiLayer.h"

#include "Gaea/Core/Timestep.h"

#include "Gaea/Renderer/Shader.h"
#include "Gaea/Renderer/Buffer.h"
#include "Gaea/Renderer/VertexArray.h"
#include "Gaea/Renderer/OrthographicCamera.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> _Window;
		ImGuiLayer* _ImGuiLayer;
		bool _Running = true;
		bool _Minimized = false;
		LayerStack _LayerStack;
		float _LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication();
}


