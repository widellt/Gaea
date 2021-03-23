#include "gapch.h"
#include "Application.h"

#include "Gaea/Core/Log.h"

#include "Input.h"
#include "Gaea/Renderer/Renderer.h"

#include <GLFW/glfw3.h>


namespace Gaea {

#define BIND_EVENT_FN(x) (std::bind(&x, this, std::placeholders::_1)) 

	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		GA_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		_Window = std::unique_ptr<Window>(Window::Create());
		_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		_ImGuiLayer = new ImGuiLayer();
		PushOverlay(_ImGuiLayer);

	}

	Application::~Application() 
	{
	}

	void Application::PushLayer(Layer* layer) {
		_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = _LayerStack.end(); it != _LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			// If an overlay handles an event, it won't propagate to layers here
			if (e.Handled)
				break;
		}
	}


	void Application::Run() {
		while (_Running) {
			float time = (float)glfwGetTime(); // TODO: Platform::GetTime
			Timestep timestep = time - _LastFrameTime;
			_LastFrameTime = time;

			// Cease updating layer stack if window minimized
			if (!_Minimized) {
				for (Layer* layer : _LayerStack) {
					layer->OnUpdate(timestep);
				}
			}
			

			_ImGuiLayer->Begin();
			for (Layer* layer : _LayerStack) {
				layer->OnImGuiRender();
			}
			_ImGuiLayer->End();
			_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0) { 
			_Minimized = true; 
			return false; 
		}

		_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
	
}