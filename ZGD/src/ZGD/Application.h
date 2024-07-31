#pragma once

#include "Core.h"
#include "Window.h"
#include "ZGD/LayerStack.h"
#include "ZGD/Events/Event.h"
#include "Events/ApplicationEvent.h"

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
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


