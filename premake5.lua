workspace "Forge"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

-- Structure output directory (e.g. Release-windows-x86_64)
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Forge/vendor/GLFW/include"

include "Forge/vendor/GLFW"

project "Forge"
	-- Destination directory for the generated project
	location "Forge"
	-- A shared library or DLL
	kind "SharedLib"
	language "C++"

	-- Destination directory for the compiled binary target
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	-- Intermediate file directory
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- Precompiled header to include
	pchheader "forgepch.h"
	-- Specifies the C++ source code file which controls the compilation of the header
	pchsource "%{prj.name}/src/forgepch.cpp"

	-- Source files
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	-- Additional include directories (avoid relative paths)
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	-- Dependency links
	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		-- Sets <RuntimeLibrary> to "MultiThreaded"
		staticruntime "On"
		-- Target OS SDK
		systemversion "latest"

		-- Adds preprocessor or compiler symbols to a project (macros)
		defines
		{
			"FORGE_PLATFORM_WINDOWS",
			"FORGE_BUILD_DLL",
			"FORGE_ENABLE_ASSERTS"
		}

		-- Output DLL to Sandbox
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "FORGE_DEBUG"
		buildoptions "/MDd"
		symbols "On" -- Debug symbol table generation

	filter "configurations:Release"
		defines "FORGE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "FORGE_DEBUG"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp" -- A console or command-line application
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Forge/vendor/spdlog/include",
		"Forge/src"
	}

	links
	{
		"Forge"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FORGE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FORGE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "FORGE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "FORGE_DEBUG"
		buildoptions "/MD"
		optimize "On"