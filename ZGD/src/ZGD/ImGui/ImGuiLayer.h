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

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}