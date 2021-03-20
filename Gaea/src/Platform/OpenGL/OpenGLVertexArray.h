#pragma once

#include "Gaea/Renderer/VertexArray.h"

namespace Gaea {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();

		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const {
			return _VertexBuffers;
		}
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const {
			return _IndexBuffer;
		}

		static VertexArray* Create();
	private:
		uint32_t _RendererID;
		std::vector<Ref<VertexBuffer>> _VertexBuffers;
		Ref<IndexBuffer> _IndexBuffer;
	};
}

