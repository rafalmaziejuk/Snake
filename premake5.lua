workspace "Project"
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
IncludeDir["glfw"] = "%{wks.location}/Engine/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/Engine/vendor/glad/include"
IncludeDir["imgui"] = "%{wks.location}/Engine/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Engine/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Engine/vendor/stb_image"
IncludeDir["freetype"] = "%{wks.location}/Engine/vendor/freetype/include"

group "Dependencies"
	include "Engine/vendor/glfw"
	include "Engine/vendor/glad"
	include "Engine/vendor/imgui"
	include "Engine/vendor/freetype"
group ""

include "Engine"
include "Snake"