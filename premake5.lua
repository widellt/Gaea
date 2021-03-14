workspace "Gaea"
	startproject "Sandbox"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

IncludeDir = {}
IncludeDir["GLFW"] = "Gaea/vendor/GLFW/include"
IncludeDir["Glad"] = "Gaea/vendor/Glad/include"
IncludeDir["ImGui"] = "Gaea/vendor/imgui"
IncludeDir["glm"] = "Gaea/vendor/glm"

group "Dependencies"
	include "Gaea/vendor/GLFW"
	include "Gaea/vendor/Glad"
	include "Gaea/vendor/imgui"
group ""

project "Gaea"
	location "Gaea"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gapch.h"
	pchsource "Gaea/src/gapch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"GA_PLATFORM_WINDOWS",
			"GA_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug" 
		defines "GA_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release" 
		defines "GA_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist" 
		defines "GA_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"Gaea/vendor/spdlog/include",
		"Gaea/src",
		"Gaea/vendor",
		"%{IncludeDir.glm}"
	}

	links {
		"Gaea"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"GA_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug" 
		defines "GA_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release" 
		defines "GA_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist" 
		defines "GA_DIST"
		runtime "Release"
		optimize "on"