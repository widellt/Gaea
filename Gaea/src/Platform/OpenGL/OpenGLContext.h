#pragma once
#include "Gaea/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Gaea {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* _WindowHandle;
	};
}	