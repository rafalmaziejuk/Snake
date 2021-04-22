#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Engine
{

	class ImGuiRenderer
	{
	public:
		static void init(void);
		static void shutdown(void);

		static void begin(void);
		static void end(void);
	};

}