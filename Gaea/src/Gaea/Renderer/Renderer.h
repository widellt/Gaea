#pragma once
#include "RendererAPI.h"
#include "RenderCommand.h"

namespace Gaea {
	

	class Renderer {
	public:

		static void BeginScene(); // TODO: Take in all scene params
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
		inline static RendererAPI::API GetAPI() {
			return RendererAPI::GetAPI();
		}
	};

	
	
}


