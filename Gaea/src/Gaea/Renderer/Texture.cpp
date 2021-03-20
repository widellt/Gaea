#include "gapch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Gaea {
	Ref<Texture2D> Texture2D::Create(const std::string& filePath) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		GA_CORE_ASSERT(false, "RendererAPI::None API not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLTexture2D>(filePath);
		}

		GA_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
}

