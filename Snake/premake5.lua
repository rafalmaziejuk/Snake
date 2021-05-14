project "Snake"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.inl"
	}

	includedirs
	{
		"%{wks.location}/Engine/src",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.freetype}"
	}

	links
	{
		"Engine",
		"glfw",
		"glad",
		"imgui",
		"freetype"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		systemversion "latest"
		
		linkoptions
		{
			"-std=c++17",
			"-pthread",
			"-lm",
			"-Wl,--no-as-needed",
			"-ldl",
			"-lGL",
			"-lXmu",
			"-lX11"
		}

	filter "configurations:Debug"
		defines "EN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"