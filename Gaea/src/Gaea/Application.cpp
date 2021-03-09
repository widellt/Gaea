#include "gapch.h"
#include "Application.h"

#include "Gaea/Log.h"

#include "GLFW/glfw3.h"

namespace Gaea {

#define BIND_EVENT_FN(x) (std::bind(&x, this, std::placeholders::_1)) 

	Application::Application() {
		_Window = std::unique_ptr<Window>(Window::Create());
		_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application() {

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		GA_CORE_TRACE("{0}", e);
	}


	void Application::Run() {
		while (_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		_Running = false;
		return true;
	}
	
}