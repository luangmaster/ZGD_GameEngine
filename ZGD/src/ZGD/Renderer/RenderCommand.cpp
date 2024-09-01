#include "zgdpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ZGD {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}