#include "gapch.h"
#include "Application.h"
#include "Gaea/Events/ApplicationEvent.h"
#include "Gaea/Log.h"

namespace Gaea {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);

		if (e.IsInCategory(EventCategoryApplication)) {
			GA_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput)) {
			GA_TRACE(e);
		}
	}
}