#pragma once

#include "Core.h"

namespace Gaea {
	class GAEA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in Client
	Application* CreateApplication();
}


