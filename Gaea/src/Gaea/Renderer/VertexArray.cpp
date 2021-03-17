#include "gapch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Gaea {
	VertexArray* VertexArray::Create(){
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		GA_CORE_ASSERT(false, "RendererAPI::None API not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();
		}

		GA_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
}
