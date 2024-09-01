#pragma once

#include "Core.h"
#include "Window.h"
#include "ZGD/LayerStack.h"
#include "ZGD/Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "ZGD/ImGui/ImGuiLayer.h"
#include "ZGD/Renderer/Shader.h"
#include "ZGD/Renderer/Buffer.h"
#include "ZGD/Renderer/VertexArray.h"
#include "ZGD/Renderer/OrthographicCamera.h"

namespace ZGD {

	class ZGD_API Application
	{
	public:
		Application();
		virtual~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	
		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


