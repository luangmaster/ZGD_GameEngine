#include <ZGD.h>
#include <ZGD/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

namespace ZGD {

	class ZGDEditorAPP : public Application
	{
	public:
		ZGDEditorAPP()
			:Application("ZGD Editor")
		{
			PushLayer(new EditorLayer());
		}
		~ZGDEditorAPP() {
	
		}

	private:

	};

	Application* CreateApplication()
	{
		return new ZGDEditorAPP();
	}
}