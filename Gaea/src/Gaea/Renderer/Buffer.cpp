#include "gapch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Gaea {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size){
		switch (Renderer::GetAPI()) 
		{
			case RendererAPI::API::None:	GA_CORE_ASSERT(false, "RendererAPI::None API not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}

		GA_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size){
		switch (Renderer::GetAPI()) 
		{
			case RendererAPI::API::None:	GA_CORE_ASSERT(false, "RendererAPI::None API not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(indices, size);
		}

		GA_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
}