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
IncludeDir["glm"] = "ZGD/vendor/glm"

include "ZGD/vendor/GLFW"
include "ZGD/vendor/Glad"
include "ZGD/vendor/imgui"

project "ZGD"

    location "ZGD"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "zgdpch.h"
	pchsource "ZGD/src/zgdpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
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
        runtime "Debug"
        symbols "On"

    filter { "configurations:Release" }
        defines { "ZGD_RELEASE" }
        runtime "Release"
        optimize "On"

    filter { "configurations:Dist" }
        defines { "ZGD_DIST" }
        runtime "Release"
        optimize "On"


project "Sandbox"

    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "ZGD/vendor/spdlog/include",
        "ZGD/src",
        "%{IncludeDir.glm}"
    }

    links
    {
        "ZGD"
    }

    filter { "system:windows" }
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "ZGD_PLATFORM_WINDOWS",
        }

    filter { "configurations:Debug" }
        defines { "ZGD_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter { "configurations:Release" }
        defines { "ZGD_RELEASE" }
        runtime "Release"
        optimize "On"

    filter { "configurations:Dist" }
        defines { "ZGD_DIST" }
        runtime "Release"
        optimize "On"