#pragma once
#include "RendererAPI.h"
#include "RenderCommand.h"
#include "OrthographicCamera.h"

#include "Shader.h"

namespace Gaea {
	

	class Renderer {
	public:

		static void BeginScene(OrthographicCamera& camera); // TODO: Take in all scene params
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
		inline static RendererAPI::API GetAPI() {
			return RendererAPI::GetAPI();
		}
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* _SceneData;
	};

	
	
}

