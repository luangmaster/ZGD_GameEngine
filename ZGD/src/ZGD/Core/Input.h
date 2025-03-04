#pragma once

#include "ZGD/Core/Core.h"
#include "ZGD/Core/KeyCodes.h"
#include "ZGD/Core/MouseButtonCodes.h"

namespace ZGD {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}