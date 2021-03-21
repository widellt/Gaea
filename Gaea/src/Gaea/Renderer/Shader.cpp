#include "gapch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Gaea {
	Shader* Shader::Create(const std::string& filePath){

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	GA_CORE_ASSERT(false, "RendererAPI::None API not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLShader(filePath);
		}

		GA_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	GA_CORE_ASSERT(false, "RendererAPI::None API not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		GA_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
}
