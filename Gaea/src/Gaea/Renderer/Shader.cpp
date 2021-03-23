#include "gapch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Gaea {
	Ref<Shader> Shader::Create(const std::string& filePath){

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	GA_CORE_ASSERT(false, "RendererAPI::None API not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(filePath);
		}

		GA_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	GA_CORE_ASSERT(false, "RendererAPI::None API not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		GA_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader> shader) {
		GA_CORE_ASSERT(!Exists(name), "Shader already exists!");
		_Shaders[name] = shader;
	}
	void ShaderLibrary::Add(const Ref<Shader> shader){
		auto& name = shader->GetName();
		Add(name, shader);
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		GA_CORE_ASSERT(Exists(name), "Shader not found!");
		return _Shaders[name];
	}
	bool ShaderLibrary::Exists(const std::string& name) const {
		return _Shaders.find(name) != _Shaders.end();
	}
}
