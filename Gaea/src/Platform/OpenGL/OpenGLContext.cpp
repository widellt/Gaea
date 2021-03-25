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

		GA_CORE_INFO("OpenGL Info : ");
		GA_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		GA_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		GA_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	#ifdef GA_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		GA_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5),
			"Gaea requires at least OpenGL version 4.5 to run!");
	#endif

	}
	void OpenGLContext::SwapBuffers(){
		glfwSwapBuffers(_WindowHandle);
	}
}