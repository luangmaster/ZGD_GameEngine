#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "ZGD/Core/Log.h"
#include "ZGD/Debug/Instrumentor.h"

#ifdef ZGD_PLATFORM_WINDOWS
	#include <Windows.h>
#endif