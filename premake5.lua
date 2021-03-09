workspace "Gaea"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

IncludeDir = {}
IncludeDir["GLFW"] = "Gaea/vendor/GLFW/include"

include "Gaea/vendor/GLFW"

project "Gaea"
	location "Gaea"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDir.GLFW}"
	}

	links {
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"GA_PLATFORM_WINDOWS",
			"GA_BUILD_DLL"
		}
		
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug" 
		defines "GA_DEBUG"
		symbols "On"
	
	filter "configurations:Release" 
		defines "GA_RELEASE"
		optimize "On"
	
	filter "configurations:Dist" 
		defines "GA_DIST"
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

	includedirs {
		"Gaea/vendor/spdlog/include",
		"Gaea/src"
	}

	links {
		"Gaea"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"GA_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug" 
		defines "GA_DEBUG"
		symbols "On"
	
	filter "configurations:Release" 
		defines "GA_RELEASE"
		optimize "On"
	
	filter "configurations:Dist" 
		defines "GA_DIST"
		optimize "On"