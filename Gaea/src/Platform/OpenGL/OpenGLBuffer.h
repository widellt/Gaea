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

		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		uint32_t _RendererID;
	};

	///////////////////////////////////////////////////////
	// Index Buffer ///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return _Count; }
	private:
		uint32_t _RendererID;
		uint32_t _Count;
	};
}