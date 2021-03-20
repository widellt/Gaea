#pragma once

#include "Gaea/Renderer/Texture.h"

namespace Gaea {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return _Width; }
		virtual uint32_t GetHeight() const override { return _Height; }

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string _Path;
		uint32_t _Width;
		uint32_t _Height;
		uint32_t _RendererID;
	};
}


