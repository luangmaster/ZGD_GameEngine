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
IncludeDir["stb_image"] = "ZGD/vendor/stb_image"

include "ZGD/vendor/GLFW"
include "ZGD/vendor/Glad"
include "ZGD/vendor/imgui"

project "ZGD"

    location "ZGD"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "zgdpch.h"
    pchsource "ZGD/src/zgdpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
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
        "%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter { "system:windows" }
        systemversion "latest"

        defines
        {
            "ZGD_PLATFORM_WINDOWS",
            "ZGD_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "USE_CONSTEXPR_FOR_FUNCTIONCALL",
        }
      
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter { "configurations:Debug" }
        defines { "ZGD_DEBUG" }
        runtime "Debug"
        symbols "on"

    filter { "configurations:Release" }
        defines { "ZGD_RELEASE" }
        runtime "Release"
        optimize "on"

    filter { "configurations:Dist" }
        defines { "ZGD_DIST" }
        runtime "Release"
        optimize "on"


project "Sandbox"

    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

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
        "ZGD/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "ZGD",
    }

    filter { "system:windows" }
        systemversion "latest"

        defines
        {
            "ZGD_PLATFORM_WINDOWS",
        }

    filter { "configurations:Debug" }
        defines { "ZGD_DEBUG" }
        runtime "Debug"
        symbols "on"

    filter { "configurations:Release" }
        defines { "ZGD_RELEASE" }
        runtime "Release"
        optimize "on"

    filter { "configurations:Dist" }
        defines { "ZGD_DIST" }
        runtime "Release"
        optimize "on"