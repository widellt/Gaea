#pragma once

#include "Core.h"

#include "Window.h"
#include "Gaea/LayerStack.h"
#include "Gaea/Events/Event.h"
#include "Gaea/Events/ApplicationEvent.h"

#include "Gaea/ImGui/ImGuiLayer.h"

#include "Gaea/Renderer/Shader.h"

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

		std::unique_ptr<Window> _Window;
		ImGuiLayer* _ImGuiLayer;
		bool _Running = true;
		LayerStack _LayerStack;

		unsigned int _VertexArray;
		unsigned int _VertexBuffer;
		unsigned int _IndexBuffer;

		std::unique_ptr<Shader> _Shader;
	private:
		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication();
}


