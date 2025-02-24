#include "Framebuffer.h"
#include "zgdpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace ZGD {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ZGD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:
			return  CreateRef<OpenGLFramebuffer>(spec);
		}

		ZGD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
