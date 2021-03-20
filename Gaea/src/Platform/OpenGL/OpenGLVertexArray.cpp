#include "gapch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Gaea {

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

	OpenGLVertexArray::OpenGLVertexArray(){
		glCreateVertexArrays(1, &_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray(){
		glDeleteVertexArrays(1, &_RendererID);
	}
	void Gaea::OpenGLVertexArray::Bind() const{
		glBindVertexArray(_RendererID);
	}

	void Gaea::OpenGLVertexArray::Unbind() const{
		glBindVertexArray(0);
	}

	void Gaea::OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer){
		GA_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		glBindVertexArray(_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}
		_VertexBuffers.push_back(vertexBuffer);

	}

	void Gaea::OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer){
		glBindVertexArray(_RendererID);
		indexBuffer->Bind();

		_IndexBuffer = indexBuffer;
	}
}
