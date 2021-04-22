#include "Engine/ImGui/ImGuiRenderer.h"
#include "Engine/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Engine
{

	void ImGuiRenderer::init(void)
	{
		ImGui::CreateContext();
		ImGuiIO &io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		Application &app = Engine::Application::get();
		GLFWwindow *window = app.get_window().get_window_handle();
		
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void ImGuiRenderer::shutdown(void)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiRenderer::begin(void)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiRenderer::end(void)
	{
		Application &app = Engine::Application::get();

		ImGuiIO &io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)app.get_window().get_width(), (float)app.get_window().get_height());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}