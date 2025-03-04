#pragma once

namespace ZGD
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define ZGD_KEY_SPACE           ::ZGD::Key::Space
#define ZGD_KEY_APOSTROPHE      ::ZGD::Key::Apostrophe    /* ' */
#define ZGD_KEY_COMMA           ::ZGD::Key::Comma         /* , */
#define ZGD_KEY_MINUS           ::ZGD::Key::Minus         /* - */
#define ZGD_KEY_PERIOD          ::ZGD::Key::Period        /* . */
#define ZGD_KEY_SLASH           ::ZGD::Key::Slash         /* / */
#define ZGD_KEY_0               ::ZGD::Key::D0
#define ZGD_KEY_1               ::ZGD::Key::D1
#define ZGD_KEY_2               ::ZGD::Key::D2
#define ZGD_KEY_3               ::ZGD::Key::D3
#define ZGD_KEY_4               ::ZGD::Key::D4
#define ZGD_KEY_5               ::ZGD::Key::D5
#define ZGD_KEY_6               ::ZGD::Key::D6
#define ZGD_KEY_7               ::ZGD::Key::D7
#define ZGD_KEY_8               ::ZGD::Key::D8
#define ZGD_KEY_9               ::ZGD::Key::D9
#define ZGD_KEY_SEMICOLON       ::ZGD::Key::Semicolon     /* ; */
#define ZGD_KEY_EQUAL           ::ZGD::Key::Equal         /* = */
#define ZGD_KEY_A               ::ZGD::Key::A
#define ZGD_KEY_B               ::ZGD::Key::B
#define ZGD_KEY_C               ::ZGD::Key::C
#define ZGD_KEY_D               ::ZGD::Key::D
#define ZGD_KEY_E               ::ZGD::Key::E
#define ZGD_KEY_F               ::ZGD::Key::F
#define ZGD_KEY_G               ::ZGD::Key::G
#define ZGD_KEY_H               ::ZGD::Key::H
#define ZGD_KEY_I               ::ZGD::Key::I
#define ZGD_KEY_J               ::ZGD::Key::J
#define ZGD_KEY_K               ::ZGD::Key::K
#define ZGD_KEY_L               ::ZGD::Key::L
#define ZGD_KEY_M               ::ZGD::Key::M
#define ZGD_KEY_N               ::ZGD::Key::N
#define ZGD_KEY_O               ::ZGD::Key::O
#define ZGD_KEY_P               ::ZGD::Key::P
#define ZGD_KEY_Q               ::ZGD::Key::Q
#define ZGD_KEY_R               ::ZGD::Key::R
#define ZGD_KEY_S               ::ZGD::Key::S
#define ZGD_KEY_T               ::ZGD::Key::T
#define ZGD_KEY_U               ::ZGD::Key::U
#define ZGD_KEY_V               ::ZGD::Key::V
#define ZGD_KEY_W               ::ZGD::Key::W
#define ZGD_KEY_X               ::ZGD::Key::X
#define ZGD_KEY_Y               ::ZGD::Key::Y
#define ZGD_KEY_Z               ::ZGD::Key::Z
#define ZGD_KEY_LEFT_BRACKET    ::ZGD::Key::LeftBracket   /* [ */
#define ZGD_KEY_BACKSLASH       ::ZGD::Key::Backslash     /* \ */
#define ZGD_KEY_RIGHT_BRACKET   ::ZGD::Key::RightBracket  /* ] */
#define ZGD_KEY_GRAVE_ACCENT    ::ZGD::Key::GraveAccent   /* ` */
#define ZGD_KEY_WORLD_1         ::ZGD::Key::World1        /* non-US #1 */
#define ZGD_KEY_WORLD_2         ::ZGD::Key::World2        /* non-US #2 */

/* Function keys */
#define ZGD_KEY_ESCAPE          ::ZGD::Key::Escape
#define ZGD_KEY_ENTER           ::ZGD::Key::Enter
#define ZGD_KEY_TAB             ::ZGD::Key::Tab
#define ZGD_KEY_BACKSPACE       ::ZGD::Key::Backspace
#define ZGD_KEY_INSERT          ::ZGD::Key::Insert
#define ZGD_KEY_DELETE          ::ZGD::Key::Delete
#define ZGD_KEY_RIGHT           ::ZGD::Key::Right
#define ZGD_KEY_LEFT            ::ZGD::Key::Left
#define ZGD_KEY_DOWN            ::ZGD::Key::Down
#define ZGD_KEY_UP              ::ZGD::Key::Up
#define ZGD_KEY_PAGE_UP         ::ZGD::Key::PageUp
#define ZGD_KEY_PAGE_DOWN       ::ZGD::Key::PageDown
#define ZGD_KEY_HOME            ::ZGD::Key::Home
#define ZGD_KEY_END             ::ZGD::Key::End
#define ZGD_KEY_CAPS_LOCK       ::ZGD::Key::CapsLock
#define ZGD_KEY_SCROLL_LOCK     ::ZGD::Key::ScrollLock
#define ZGD_KEY_NUM_LOCK        ::ZGD::Key::NumLock
#define ZGD_KEY_PRINT_SCREEN    ::ZGD::Key::PrintScreen
#define ZGD_KEY_PAUSE           ::ZGD::Key::Pause
#define ZGD_KEY_F1              ::ZGD::Key::F1
#define ZGD_KEY_F2              ::ZGD::Key::F2
#define ZGD_KEY_F3              ::ZGD::Key::F3
#define ZGD_KEY_F4              ::ZGD::Key::F4
#define ZGD_KEY_F5              ::ZGD::Key::F5
#define ZGD_KEY_F6              ::ZGD::Key::F6
#define ZGD_KEY_F7              ::ZGD::Key::F7
#define ZGD_KEY_F8              ::ZGD::Key::F8
#define ZGD_KEY_F9              ::ZGD::Key::F9
#define ZGD_KEY_F10             ::ZGD::Key::F10
#define ZGD_KEY_F11             ::ZGD::Key::F11
#define ZGD_KEY_F12             ::ZGD::Key::F12
#define ZGD_KEY_F13             ::ZGD::Key::F13
#define ZGD_KEY_F14             ::ZGD::Key::F14
#define ZGD_KEY_F15             ::ZGD::Key::F15
#define ZGD_KEY_F16             ::ZGD::Key::F16
#define ZGD_KEY_F17             ::ZGD::Key::F17
#define ZGD_KEY_F18             ::ZGD::Key::F18
#define ZGD_KEY_F19             ::ZGD::Key::F19
#define ZGD_KEY_F20             ::ZGD::Key::F20
#define ZGD_KEY_F21             ::ZGD::Key::F21
#define ZGD_KEY_F22             ::ZGD::Key::F22
#define ZGD_KEY_F23             ::ZGD::Key::F23
#define ZGD_KEY_F24             ::ZGD::Key::F24
#define ZGD_KEY_F25             ::ZGD::Key::F25

/* Keypad */
#define ZGD_KEY_KP_0            ::ZGD::Key::KP0
#define ZGD_KEY_KP_1            ::ZGD::Key::KP1
#define ZGD_KEY_KP_2            ::ZGD::Key::KP2
#define ZGD_KEY_KP_3            ::ZGD::Key::KP3
#define ZGD_KEY_KP_4            ::ZGD::Key::KP4
#define ZGD_KEY_KP_5            ::ZGD::Key::KP5
#define ZGD_KEY_KP_6            ::ZGD::Key::KP6
#define ZGD_KEY_KP_7            ::ZGD::Key::KP7
#define ZGD_KEY_KP_8            ::ZGD::Key::KP8
#define ZGD_KEY_KP_9            ::ZGD::Key::KP9
#define ZGD_KEY_KP_DECIMAL      ::ZGD::Key::KPDecimal
#define ZGD_KEY_KP_DIVIDE       ::ZGD::Key::KPDivide
#define ZGD_KEY_KP_MULTIPLY     ::ZGD::Key::KPMultiply
#define ZGD_KEY_KP_SUBTRACT     ::ZGD::Key::KPSubtract
#define ZGD_KEY_KP_ADD          ::ZGD::Key::KPAdd
#define ZGD_KEY_KP_ENTER        ::ZGD::Key::KPEnter
#define ZGD_KEY_KP_EQUAL        ::ZGD::Key::KPEqual

#define ZGD_KEY_LEFT_SHIFT      ::ZGD::Key::LeftShift
#define ZGD_KEY_LEFT_CONTROL    ::ZGD::Key::LeftControl
#define ZGD_KEY_LEFT_ALT        ::ZGD::Key::LeftAlt
#define ZGD_KEY_LEFT_SUPER      ::ZGD::Key::LeftSuper
#define ZGD_KEY_RIGHT_SHIFT     ::ZGD::Key::RightShift
#define ZGD_KEY_RIGHT_CONTROL   ::ZGD::Key::RightControl
#define ZGD_KEY_RIGHT_ALT       ::ZGD::Key::RightAlt
#define ZGD_KEY_RIGHT_SUPER     ::ZGD::Key::RightSuper
#define ZGD_KEY_MENU            ::ZGD::Key::Menu