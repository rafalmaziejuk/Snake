#include "Engine/Core/Application.h"
#include "Engine/Core/EngineAssert.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/ImGui/ImGuiRenderer.h"

namespace Engine
{

	Application * Application::appInstance = nullptr;

	Application::Application(const std::string &name)
	{
		EN_ASSERT(!appInstance);
		appInstance = this;

		m_window = Window::create(name);

		Renderer::init(m_window->get_width(), m_window->get_height());
		Renderer::set_viewport(m_window->get_width(), m_window->get_height());
		Renderer::set_clear_color({ 0.0f, 0.0f, 0.0f, 1.0f });

		ImGuiRenderer::init();
	}

	Application::~Application(void)
	{
		Renderer::shutdown();
	}

    void Application::close(void)
    {
		m_isRunning = false;
    }

	void Application::run(void)
	{
		float timeSinceLastUpdate = 0.0f;

		while (m_isRunning)
		{
			float time = (float)glfwGetTime();
			float timestep = time - timeSinceLastUpdate;
			timeSinceLastUpdate = time;

			on_update(timestep);

			Renderer::clear();

			on_render();

			ImGuiRenderer::begin();
			on_imgui_render();
			ImGuiRenderer::end();

			m_window->update();
		}
	}

}