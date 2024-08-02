workspace "ZGD"
	startproject "Sandbox"
    architecture "x64"
    configurations { "Debug", "Release", "Dist"}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "ZGD/vendor/GLFW/include"
IncludeDir["Glad"] = "ZGD/vendor/Glad/include"
IncludeDir["ImGui"] = "ZGD/vendor/imgui"

include "ZGD/vendor/GLFW"
include "ZGD/vendor/Glad"
include "ZGD/vendor/imgui"

project "ZGD"

    location "ZGD"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "zgdpch.h"
	pchsource "ZGD/src/zgdpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }
	
	links
	{
		"GLFW",
        "Glad",
        "ImGui",
		"opengl32.lib"
	}

    filter { "system:windows" }
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "ZGD_PLATFORM_WINDOWS",
            "ZGD_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
      
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter { "configurations:Debug" }
        defines { "ZGD_DEBUG" }
        buildoptions "/MDd"
        symbols "On"

    filter { "configurations:Release" }
        defines { "ZGD_RELEASE" }
        buildoptions "/MD"
        optimize "On"

    filter { "configurations:Dist" }
        defines { "ZGD_DIST" }
         buildoptions "/MD"
        optimize "On"


project "Sandbox"

    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "ZGD/vendor/spdlog/include",
        "ZGD/src"
    }

    links
    {
        "ZGD"
    }

    filter { "system:windows" }
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "ZGD_PLATFORM_WINDOWS",
        }

    filter { "configurations:Debug" }
        defines { "ZGD_DEBUG" }
        buildoptions "/MDd"
        symbols "On"

    filter { "configurations:Release" }
        defines { "ZGD_RELEASE" }
        buildoptions "/MD"
        optimize "On"

    filter { "configurations:Dist" }
        defines { "ZGD_DIST" }
        buildoptions "/MD"
        optimize "On"