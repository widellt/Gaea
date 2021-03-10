#include "gapch.h"
#include "Application.h"

#include "Gaea/Log.h"

#include <glad/glad.h>

namespace Gaea {

#define BIND_EVENT_FN(x) (std::bind(&x, this, std::placeholders::_1)) 

	Application::Application() {
		_Window = std::unique_ptr<Window>(Window::Create());
		_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		unsigned int id;
		glGenVertexArrays(1, &id);
	}

	Application::~Application() 
	{
	}

	void Application::PushLayer(Layer* layer) {
		_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {
		_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = _LayerStack.end(); it != _LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			// If an overlay handles an event, it won't propagate to layers here
			if (e.Handled)
				break;
		}
	}


	void Application::Run() {
		while (_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : _LayerStack) {
				layer->OnUpdate();
			}

			_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		_Running = false;
		return true;
	}
	
}