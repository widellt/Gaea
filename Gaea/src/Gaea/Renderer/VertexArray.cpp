#include "gapch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Gaea {
	VertexArray* VertexArray::Create(){
		switch (Renderer::GetRenderAPI())
		{
		case RendererAPI::None:		GA_CORE_ASSERT(false, "RendererAPI::None API not supported!"); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		GA_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
}
