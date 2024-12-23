#include "zgdpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace ZGD {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ZGD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:
			return  CreateRef<OpenGLVertexBuffer>(size);
		}

		ZGD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	 Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				ZGD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:
				return  CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		
		ZGD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	 Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		 switch (Renderer::GetAPI())
		 {
			case RendererAPI::API::None:
				ZGD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLIndexBuffer>(indices, count);
		 }

		 ZGD_CORE_ASSERT(false, "Unknown RendererAPI!");
		 return nullptr;
	}
}