#pragma once

#include "Gaea.h"

class Sandbox2D : public Gaea::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Gaea::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Gaea::Event& e) override;

private:
	// Camera
	Gaea::OrthographicCameraController _CameraController;

	// Temp
	Gaea::Ref<Gaea::VertexArray> _SquareVA;
	Gaea::Ref<Gaea::Shader> _FlatColorShader;


	// Shader
	glm::vec4 _SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

};

