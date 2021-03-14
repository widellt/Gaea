#include "gapch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "Gaea/Application.h"

namespace Gaea {
	Input* Input::s_Instance = new WindowsInput();

	// Keys
	bool WindowsInput::IsKeyPressedImpl(int keycode) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	// Mouse
	bool WindowsInput::IsMouseButtonPressedImpl(int button){
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::GetMousePosImpl() {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;

		glfwGetCursorPos(window, &xPos, &yPos);

		return std::pair<float, float>((float)xPos, (float)yPos);
	}
	float WindowsInput::GetMouseXImpl(){
		auto [x, y] = GetMousePosImpl();

		return x;
	}
	float WindowsInput::GetMouseYImpl(){
		auto [x, y] = GetMousePosImpl();

		return y;
	}
	
}