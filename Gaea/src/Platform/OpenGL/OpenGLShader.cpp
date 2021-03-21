#include "gapch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Gaea {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex") {
			return GL_VERTEX_SHADER;
		}
		else if (type == "fragment" || type == "pixel") {
			return GL_FRAGMENT_SHADER;
		}

		GA_CORE_ASSERT(false, "Uknown shader type!");
		return 0;
	}
	OpenGLShader::OpenGLShader(const std::string& filePath){
		std::string source = ReadFile(filePath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		// Extract name from filePath
		auto lastSlash = filePath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filePath.rfind('.');
		auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
		_Name = filePath.substr(lastSlash, count);
	}
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: _Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}
	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(0);
	}
	void OpenGLShader::Bind() const {
		glUseProgram(_RendererID);
	}
	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}
	void OpenGLShader::UploadUniformInt(const std::string& name, const int val){
		GLint location = glGetUniformLocation(_RendererID, name.c_str());
		glUniform1i(location, val);
	}
	void OpenGLShader::UploadUniformFloat(const std::string& name, float val){
		GLint location = glGetUniformLocation(_RendererID, name.c_str());
		glUniform1f(location, val);
	}
	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vals){
		GLint location = glGetUniformLocation(_RendererID, name.c_str());
		glUniform2f(location, vals.x, vals.y);
	}
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vals){
		GLint location = glGetUniformLocation(_RendererID, name.c_str());
		glUniform3f(location, vals.x, vals.y, vals.z);
	}
	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vals) {
		GLint location = glGetUniformLocation(_RendererID, name.c_str());
		glUniform4f(location, vals.x, vals.y, vals.z, vals.w);
	}
	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix){
		GLint location = glGetUniformLocation(_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = glGetUniformLocation(_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	std::string OpenGLShader::ReadFile(const std::string& filePath){

		std::string result;
		std::ifstream in(filePath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else {
			GA_CORE_ERROR("Could not open file '{0}'", filePath);
		}

		return result;
	}
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source){

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			GA_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			GA_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] =
				source.substr(nextLinePos, 
					pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}
	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources){

		GLuint program = glCreateProgram();
		GA_CORE_ASSERT(shaderSources <= 2, "Only two shaders supported currently");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;

		for (auto& keyVal : shaderSources) {
			GLenum type = keyVal.first;
			const std::string& source = keyVal.second;

			// Create an empty vertex shader handle
			GLuint shader = glCreateShader(type);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCStr= source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// Compile the shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				GA_CORE_ERROR("{0}", infoLog.data());
				GA_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			// Vertex and fragment shaders are successfully compiled.
			// Now time to link them together into a program.

			// Attach our shaders to our program
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++]  = shader;
		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto id : glShaderIDs) {
				glDeleteShader(id);
			}
			

			GA_CORE_ERROR("{0}", infoLog.data());
			GA_CORE_ASSERT(false, "Shader linking failure!");
			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderIDs) {
			glDetachShader(program, id);
		}

		// Get a program object.
		_RendererID = program;
	}
}