#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <cstdint>

struct GLFWwindow;

class ImGuiRenderer
{
public:
	static void init(GLFWwindow *window);
	static void shutdown(void);

	static void begin(void);
	static void end(uint16_t width, uint16_t height);
};