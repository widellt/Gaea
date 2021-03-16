#include "gapch.h"
#include "Application.h"

#include "Gaea/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Gaea {

#define BIND_EVENT_FN(x) (std::bind(&x, this, std::placeholders::_1)) 

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}

		GA_CORE_ASSERT(false, "Uknown ShaderDataType!");
		return 0;
	}

	Application::Application() {
		GA_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		_Window = std::unique_ptr<Window>(Window::Create());
		_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		_ImGuiLayer = new ImGuiLayer();
		PushOverlay(_ImGuiLayer);

		glGenVertexArrays(1, &_VertexArray);
		glBindVertexArray(_VertexArray);

		float vertices[3 * 7] = { 
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 0.8f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 0.8f
		};

		_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
			};

			_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;

		const auto& layout = _VertexBuffer->GetLayout();

		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}

		uint32_t indices[3] = { 0, 1, 2 };
		_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position; 
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
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

		_Shader.reset(new Shader(vertexSrc, fragmentSrc));

	}

	Application::~Application() 
	{
	}

	void Application::PushLayer(Layer* layer) {
		_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = _LayerStack.end(); it != _LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			// If an overlay handles an event, it won't propagate to layers here
			if (e.Handled)
				break;
		}
	}


	void Application::Run() {
		while (_Running) {
			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Should bind before instantiating vertex/frag elements for later use with DX, Vulkan, etc.
			_Shader->Bind();
			glBindVertexArray(_VertexArray);
			glDrawElements(GL_TRIANGLES, _IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : _LayerStack) {
				layer->OnUpdate();
			}

			_ImGuiLayer->Begin();
			for (Layer* layer : _LayerStack) {
				layer->OnImGuiRender();
			}
			_ImGuiLayer->End();
			_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		_Running = false;
		return true;
	}
	
}