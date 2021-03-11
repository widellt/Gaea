workspace "Gaea"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

IncludeDir = {}
IncludeDir["GLFW"] = "Gaea/vendor/GLFW/include"
IncludeDir["Glad"] = "Gaea/vendor/Glad/include"
IncludeDir["ImGui"] = "Gaea/vendor/imgui"

include "Gaea/vendor/GLFW"
include "Gaea/vendor/Glad"
include "Gaea/vendor/imgui"

project "Gaea"
	location "Gaea"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gapch.h"
	pchsource "Gaea/src/gapch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"GA_PLATFORM_WINDOWS",
			"GA_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug" 
		defines "GA_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release" 
		defines "GA_RELEASE"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist" 
		defines "GA_DIST"
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

	includedirs {
		"Gaea/vendor/spdlog/include",
		"Gaea/src"
	}

	links {
		"Gaea"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"GA_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug" 
		defines "GA_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release" 
		defines "GA_RELEASE"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist" 
		defines "GA_DIST"
		runtime "Release"
		optimize "On"