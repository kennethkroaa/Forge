workspace "Forge"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Forge"
	location "Forge"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FORGE_PLATFORM_WINDOWS",
			"FORGE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "FORGE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "FORGE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "FORGE_DEBUG"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
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
		symbols "On"

	filter "configurations:Release"
		defines "FORGE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "FORGE_DEBUG"
		optimize "On"