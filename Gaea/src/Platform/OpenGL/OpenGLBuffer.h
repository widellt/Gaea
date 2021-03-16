#pragma once

#include "Gaea/Renderer/Buffer.h"

namespace Gaea {
	///////////////////////////////////////////////////////
	// Vertex Buffer ///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return _Layout; };
		virtual void SetLayout(BufferLayout& layout) override { _Layout = layout; };
	private:
		uint32_t _RendererID;
		BufferLayout _Layout;

	};

	///////////////////////////////////////////////////////
	// Index Buffer ///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const { return _Count; }
	private:
		uint32_t _RendererID;
		uint32_t _Count;
	};
}