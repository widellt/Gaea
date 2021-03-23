#pragma once
#include "Gaea/Renderer/OrthographicCamera.h"
#include "Gaea/Core/Timestep.h"

#include "Gaea/Events/ApplicationEvent.h"
#include "Gaea/Events/MouseEvent.h"

namespace Gaea {
	class OrthographicCameraController{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false); // AR * 2 units

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() {return _Camera;}
		const OrthographicCamera& GetCamera() const { return _Camera; }

		float GetZoomLevel() const { return _ZoomLevel; }
		void SetZoomLevel(float zoomLevel) { _ZoomLevel = zoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool WindowResize(WindowResizeEvent& e);
	private:
		float _AspectRatio;
		float _ZoomLevel = 1.0f;
		OrthographicCamera _Camera;

		bool _Rotation;
		glm::vec3 _CameraPosition = { 0.0f, 0.0f,0.0f };
		float _CameraRotation = 0.0f;
		float _CameraTranslationSpeed = 5.0f;
		float _CameraRotationSpeed = 180.0f;
	};
}


