workspace "Forge"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["glad"] = "Forge/vendor/glad/include"
IncludeDir["ImGui"] = "Forge/vendor/ImGui"

group "Dependencies"
	include "Forge/vendor/GLFW"
	include "Forge/vendor/glad"
	include "Forge/vendor/ImGui"

group ""

project "Forge"
	-- Destination directory for the generated project
	location "Forge"
	-- A shared library or DLL
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}"
	}

	-- Dependency links
	links
	{
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		-- Target OS SDK
		systemversion "latest"

		-- Adds preprocessor or compiler symbols to a project (macros)
		defines
		{
			"FORGE_PLATFORM_WINDOWS",
			"FORGE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		-- Output DLL to Sandbox
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "FORGE_DEBUG"
		runtime "Debug"
		symbols "On" -- Debug symbol table generation

	filter "configurations:Release"
		defines "FORGE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FORGE_DEBUG"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp" -- A console or command-line application
	language "C++"
	staticruntime "off"

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
		systemversion "latest"

		defines
		{
			"FORGE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FORGE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "FORGE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FORGE_DEBUG"
		runtime "Release"
		optimize "On"