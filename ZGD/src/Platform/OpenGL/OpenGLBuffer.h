#pragma once
#include "ZGD/Renderer/Buffer.h"

namespace ZGD
{
	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; };
		virtual void SetLayout(const BufferLayout& layout) override 
		{ 
			m_Layout = layout; 
		};

	private:
		uint32_t m_VertexBufferID;
		BufferLayout m_Layout;
	};


	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();
		virtual void Bind() const;
		virtual void Unbind() const;

		virtual inline uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_IndexBufferID;
		uint32_t m_Count;
	};
}