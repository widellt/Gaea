#pragma once

#include "Gaea/Renderer/RendererAPI.h"

namespace Gaea {
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Gaea::Ref<VertexArray>& vertexArray) override;
	};
}


