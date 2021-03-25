#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() 
	: Layer("Sandbox2D"), _CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach(){
	
	_SquareVA = Gaea::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Gaea::Ref<Gaea::VertexBuffer> squareVB;
	squareVB.reset(Gaea::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	Gaea::BufferLayout squareLayout = {
		{ Gaea::ShaderDataType::Float3, "a_Position" }
	};
	squareVB->SetLayout(squareLayout);
	_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Gaea::Ref<Gaea::IndexBuffer> squareIB;
	squareIB.reset(Gaea::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	_SquareVA->SetIndexBuffer(squareIB);

	_FlatColorShader = Gaea::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach(){
}

void Sandbox2D::OnUpdate(Gaea::Timestep ts){
	//Update
	_CameraController.OnUpdate(ts);

	// Render
	Gaea::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	Gaea::RenderCommand::Clear();

	Gaea::Renderer::BeginScene(_CameraController.GetCamera());

	std::dynamic_pointer_cast<Gaea::OpenGLShader>(_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Gaea::OpenGLShader>(_FlatColorShader)->UploadUniformFloat4("u_Color", _SquareColor);

	Gaea::Renderer::Submit(_FlatColorShader, _SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Gaea::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender(){
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Gaea::Event& e){
	_CameraController.OnEvent(e);
}
