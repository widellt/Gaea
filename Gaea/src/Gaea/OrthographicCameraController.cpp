#include "gapch.h"
#include "OrthographicCameraController.h"

#include "Gaea/Input.h"
#include "Gaea/KeyCodes.h"

namespace Gaea {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) 
		: _AspectRatio(aspectRatio), _Camera(-_AspectRatio * _ZoomLevel, _AspectRatio * _ZoomLevel, -_ZoomLevel, _ZoomLevel), _Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts) {
		if (Input::IsKeyPressed(GA_KEY_A)) { _CameraPosition.x += _CameraTranslationSpeed * ts; }
		else if (Input::IsKeyPressed(GA_KEY_D)) { _CameraPosition.x -= _CameraTranslationSpeed * ts; }

		if (Input::IsKeyPressed(GA_KEY_W)) { _CameraPosition.y -= _CameraTranslationSpeed * ts; }
		else if (Input::IsKeyPressed(GA_KEY_S)) { _CameraPosition.y += _CameraTranslationSpeed * ts; }

		if (_Rotation) {
			if (Input::IsKeyPressed(GA_KEY_Q)) { _CameraRotation -= _CameraRotationSpeed * ts; }
			if (Input::IsKeyPressed(GA_KEY_E)) { _CameraRotation += _CameraRotationSpeed * ts; }
		}

		_Camera.SetPosition(_CameraPosition);
		_Camera.SetRotation(_CameraRotation);

		_CameraTranslationSpeed = _ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(GA_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled);
		dispatcher.Dispatch<WindowResizeEvent>(GA_BIND_EVENT_FN(OrthographicCameraController::WindowResize);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		_ZoomLevel -= e.GetYOffset() * 0.25f;
		_ZoomLevel = std::max(_ZoomLevel, 0.25f);
		_Camera.SetProjection(-_AspectRatio * _ZoomLevel, _AspectRatio * _ZoomLevel, -_ZoomLevel, _ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::WindowResize(WindowResizeEvent& e) {
		_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		_Camera.SetProjection(-_AspectRatio * _ZoomLevel, _AspectRatio * _ZoomLevel, -_ZoomLevel, _ZoomLevel);
		return false;
	}
}

