#include "gapch.h"
#include "WindowsWindow.h"

#include "Gaea/Events/ApplicationEvent.h"
#include "Gaea/Events/KeyEvent.h"
#include "Gaea/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Gaea {
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* msg) {
		GA_CORE_ERROR("GLFW Error ({0}): {1}", error, msg);
	}

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		_Data.Title = props.Title;
		_Data.Width = props.Width;
		_Data.Height = props.Height;

		GA_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		

		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			GA_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		_Window = glfwCreateWindow((int)props.Width, (int)props.Height, _Data.Title.c_str(), nullptr, nullptr);

		_Context = new OpenGLContext(_Window);
		_Context->Init();

		glfwSetWindowUserPointer(_Window, &_Data);
		SetVSync(true);

		// Set GLFW callbacks 
		glfwSetWindowSizeCallback(_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_RELEASE:{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1); // Will implement repeat count in the future
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);

		});

		glfwSetMouseButtonCallback(_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);

		});
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return _Data.VSync;
	}
}