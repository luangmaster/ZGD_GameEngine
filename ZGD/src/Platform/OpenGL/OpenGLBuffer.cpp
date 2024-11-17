#include "zgdpch.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"

namespace ZGD {
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		ZGD_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_VertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		ZGD_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_VertexBufferID);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		ZGD_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		ZGD_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/// IndexBuffer

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		:m_Count(count)
	{
		ZGD_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_IndexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		ZGD_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_IndexBufferID);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		ZGD_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	}
	void OpenGLIndexBuffer::Unbind() const
	{
		ZGD_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
