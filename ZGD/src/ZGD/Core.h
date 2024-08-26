#pragma once

#ifdef ZGD_PLATFORM_WINDOWS
	#ifdef ZGD_DYNAMIC_LINK
		#ifdef ZGD_BUILD_DLL
			#define ZGD_API __declspec(dllexport)
		#else
			#define ZGD_API __declspec(dllimport)
		#endif // ZGD_BUILD_DLL
	#else
		#define ZGD_API
	#endif
#else
	#error ZGD only support windows!
#endif // ZGD_PLATFORM_WINDOWS

#ifdef ZGD_DEBUG
	#define ZGD_ENABLE_ASSERTS
#endif

#ifdef ZGD_ENABLE_ASSERTS
	#define ZGD_ASSERT(x, ...) { if(!(x)) { ZGD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ZGD_CORE_ASSERT(x, ...) { if(!(x)) { ZGD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ZGD_ASSERT(x, ...)
	#define ZGD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
