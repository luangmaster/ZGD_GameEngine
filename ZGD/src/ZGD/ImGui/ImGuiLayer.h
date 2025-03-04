#pragma once

#include "ZGD/Core/Layer.h"

#include "ZGD/Events/ApplicationEvent.h"
#include "ZGD/Events/KeyEvent.h"
#include "ZGD/Events/MouseEvent.h"

namespace ZGD {

	class ZGD_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}