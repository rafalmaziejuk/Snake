project "Snake"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.freetype}"
	}

	filter "system:windows"
		systemversion "latest"

		defines { }

		links
		{
			"glfw",
			"glad",
			"imgui",
			"freetype",
			"opengl32.lib"
		}

	filter "system:linux"
		systemversion "latest"
			
		links
		{
			"glfw",
			"glad",
			"imgui",
			"freetype"
		}
		
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
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"