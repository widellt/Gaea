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
IncludeDir["Glad"] = "Gaea/vendor/Glad/include"

include "Gaea/vendor/GLFW"
include "Gaea/vendor/Glad"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links {
		"GLFW",
		"Glad",
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
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release" 
		defines "GA_RELEASE"
		buildoptions "/MD"
		optimize "On"
	
	filter "configurations:Dist" 
		defines "GA_DIST"
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
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release" 
		defines "GA_RELEASE"
		buildoptions "/MD"
		optimize "On"
	
	filter "configurations:Dist" 
		defines "GA_DIST"
		buildoptions "/MD"
		optimize "On"