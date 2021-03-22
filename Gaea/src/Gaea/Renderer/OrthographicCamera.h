#pragma once
#include <glm/glm.hpp>

namespace Gaea {

	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() { return _Position; }
		void SetPosition(const glm::vec3& position) { _Position = position; RecalculateViewMatrix(); }

		const float GetRotation() { return _Rotation; }
		void SetRotation(const float& rotation) { _Rotation = rotation; RecalculateViewMatrix(); }


		const glm::mat4& GetProjectionMatrix() const { return _ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return _ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return _ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 _ProjectionMatrix;
		glm::mat4 _ViewMatrix;
		glm::mat4 _ViewProjectionMatrix;

		glm::vec3 _Position{0.0f, 0.0f, 0.0f};
		float _Rotation = 0;
	};
}

