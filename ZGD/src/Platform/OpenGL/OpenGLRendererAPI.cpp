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

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}