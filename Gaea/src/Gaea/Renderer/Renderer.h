#pragma once
#include "RendererAPI.h"
#include "RenderCommand.h"
#include "OrthographicCamera.h"

#include "Shader.h"

namespace Gaea {
	

	class Renderer {
	public:

		static void Init();

		static void BeginScene(OrthographicCamera& camera); // TODO: Take in all scene params
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
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


