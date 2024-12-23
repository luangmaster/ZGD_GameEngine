#include "zgdpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

#define GLCALL(x) do {\
					GLClearError();\
					x;\
					ZGD_CORE_ASSERT(GLLogCall(#x, __FILE__, __LINE__), "error!!!");\
				} while (0);

//#define GLCALL(x) do{x;} while(0);

namespace ZGD {


	static void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	static bool GLLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			ZGD_CORE_INFO("GLLogCall error:{0} {1} {2} {3}", error, function, file, line);
			return false;
		}
		return true;
	}
	void OpenGLRendererAPI::Init() {
		ZGD_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}