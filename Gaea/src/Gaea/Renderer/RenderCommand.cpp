#include "gapch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Gaea {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}