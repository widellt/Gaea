#include <Gaea.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Gaea::Layer {
public:
	ExampleLayer()
		: Layer("Example"),  _CameraController(1280.0f/720.0f)
	{
		_VertexArray.reset(Gaea::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 0.8f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 0.8f
		};

		Gaea::Ref<Gaea::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Gaea::VertexBuffer::Create(vertices, sizeof(vertices)));
		Gaea::BufferLayout layout = {
			{ Gaea::ShaderDataType::Float3, "a_Position" },
			{ Gaea::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Gaea::Ref<Gaea::IndexBuffer> indexBuffer;
		indexBuffer.reset(Gaea::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		_VertexArray->SetIndexBuffer(indexBuffer);

		_SquareVA.reset(Gaea::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Gaea::Ref<Gaea::VertexBuffer> squareVB;
		squareVB.reset(Gaea::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Gaea::BufferLayout squareLayout = {
			{ Gaea::ShaderDataType::Float3, "a_Position" },
			{ Gaea::ShaderDataType::Float2, "a_TexCoord" }
		};
		squareVB->SetLayout(squareLayout);
		_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Gaea::Ref<Gaea::IndexBuffer> squareIB;
		squareIB.reset(Gaea::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position; 
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}

		)";

		_Shader = Gaea::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position; 

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}

		)";

		_FlatColorShader = Gaea::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = _ShaderLibrary.Load("assets/shaders/Texture.glsl");
		_Texture = Gaea::Texture2D::Create("assets/textures/checkerboard.png");
		_TransTexture = Gaea::Texture2D::Create("assets/textures/alpha.png");

		std::dynamic_pointer_cast<Gaea::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Gaea::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Gaea::Timestep ts) override {
		//Update
		_CameraController.OnUpdate(ts);

		// Render
		Gaea::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		Gaea::RenderCommand::Clear();

		Gaea::Renderer::BeginScene(_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Gaea::OpenGLShader>(_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Gaea::OpenGLShader>(_FlatColorShader)->UploadUniformFloat3("u_Color", _SquareColor);

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				
				Gaea::Renderer::Submit(_FlatColorShader, _SquareVA, transform);
			}
		}

		auto textureShader = _ShaderLibrary.Get("Texture");

		_Texture->Bind();
		Gaea::Renderer::Submit(textureShader, _SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		_TransTexture->Bind();
		Gaea::Renderer::Submit(textureShader, _SquareVA, glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Gaea::Renderer::Submit(_Shader, _VertexArray);
		
		Gaea::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(_SquareColor));
		ImGui::End();
	}

	void OnEvent(Gaea::Event& e) override {
		_CameraController.OnEvent(e);
	}

private:
	Gaea::ShaderLibrary _ShaderLibrary;
	Gaea::Ref<Gaea::Shader> _Shader;
	Gaea::Ref<Gaea::VertexArray> _VertexArray;

	Gaea::Ref<Gaea::Shader> _FlatColorShader;
	Gaea::Ref<Gaea::VertexArray> _SquareVA;

	Gaea::Ref<Gaea::Texture2D> _Texture, _TransTexture;

	// Camera
	Gaea::OrthographicCameraController _CameraController;

	// Shader
	glm::vec3 _SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Gaea::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	
	~Sandbox() {

	}

};

Gaea::Application* Gaea::CreateApplication() {
	return new Sandbox();
}
