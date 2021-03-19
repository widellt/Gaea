#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Gaea {
	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind(); 
		void Unbind();

		void UploadUniformFloat4(const std::string& name, const glm::vec4& vals);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t _RendererID;
	};
};