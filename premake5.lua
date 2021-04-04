workspace "Snake"
    architecture "x64"
    startproject "Snake"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glfw"] = "%{wks.location}/Snake/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/Snake/vendor/glad/include"
IncludeDir["imgui"] = "%{wks.location}/Snake/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Snake/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Snake/vendor/stb_image"
IncludeDir["freetype"] = "%{wks.location}/Snake/vendor/freetype/include"

group "Dependencies"
	include "Snake/vendor/glfw"
	include "Snake/vendor/glad"
	include "Snake/vendor/imgui"
	include "Snake/vendor/freetype"
group ""

include "Snake"
