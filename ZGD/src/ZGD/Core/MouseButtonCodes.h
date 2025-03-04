#pragma once

namespace ZGD
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define ZGD_MOUSE_BUTTON_0      ::ZGD::Mouse::Button0
#define ZGD_MOUSE_BUTTON_1      ::ZGD::Mouse::Button1
#define ZGD_MOUSE_BUTTON_2      ::ZGD::Mouse::Button2
#define ZGD_MOUSE_BUTTON_3      ::ZGD::Mouse::Button3
#define ZGD_MOUSE_BUTTON_4      ::ZGD::Mouse::Button4
#define ZGD_MOUSE_BUTTON_5      ::ZGD::Mouse::Button5
#define ZGD_MOUSE_BUTTON_6      ::ZGD::Mouse::Button6
#define ZGD_MOUSE_BUTTON_7      ::ZGD::Mouse::Button7
#define ZGD_MOUSE_BUTTON_LAST   ::ZGD::Mouse::ButtonLast
#define ZGD_MOUSE_BUTTON_LEFT   ::ZGD::Mouse::ButtonLeft
#define ZGD_MOUSE_BUTTON_RIGHT  ::ZGD::Mouse::ButtonRight
#define ZGD_MOUSE_BUTTON_MIDDLE ::ZGD::Mouse::ButtonMiddle