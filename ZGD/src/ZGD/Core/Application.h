#pragma once

#include "Core.h"
#include "Window.h"
#include "ZGD/Core/LayerStack.h"
#include "ZGD/Events/Event.h"
#include "ZGD/Events/ApplicationEvent.h"
#include "ZGD/ImGui/ImGuiLayer.h"
#include "ZGD/Renderer/Shader.h"
#include "ZGD/Renderer/Buffer.h"
#include "ZGD/Renderer/VertexArray.h"
#include "ZGD/Renderer/OrthographicCamera.h"
#include "ZGD/Core/TimeStep.h"

namespace ZGD {

	class Application
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
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		TimeStep m_Timestep;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}