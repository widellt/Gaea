#pragma once

#include "Gaea/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Gaea {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string& name, const int val);

		void UploadUniformFloat(const std::string& name, float vals);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vals);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vals);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vals);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t _RendererID;
	};
};