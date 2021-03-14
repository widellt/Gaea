#include "gapch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Gaea {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: _WindowHandle(windowHandle)
	{
		GA_CORE_ASSERT(windowHandle, "Window handle is NULL!");
	}

	void OpenGLContext::Init(){
		glfwMakeContextCurrent(_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GA_CORE_ASSERT(status, "Failed to initialize Glad!");
	}
	void OpenGLContext::SwapBuffers(){
		glfwSwapBuffers(_WindowHandle);
	}
}