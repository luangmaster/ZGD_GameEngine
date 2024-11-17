#include "zgdpch.h"
#include "OpenGLContext.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace ZGD {

	ZGD::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		:m_WindowHandle(windowHandle)
	{
		ZGD_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
	}

	void ZGD::OpenGLContext::Init()
	{
		ZGD_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ZGD_CORE_ASSERT(status, "Failed to initailize Glad!");

		ZGD_CORE_INFO("OpenGL Info:");
		ZGD_CORE_INFO(" Vendor: {0}", (const char *)glGetString(GL_VENDOR));
		ZGD_CORE_INFO(" Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		ZGD_CORE_INFO(" Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void ZGD::OpenGLContext::SwapBuffers()
	{
		ZGD_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}
