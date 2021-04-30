#include "Engine/Core/Core.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/EngineAssert.h"
#include "Engine/Events/WindowEvent.h"
#include "Engine/Core/Layer.h"

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
		m_window->set_event_callback(EN_BIND_EVENT(Application::on_event));

		Renderer::init(m_window->get_width(), m_window->get_height());
		Renderer::set_viewport(m_window->get_width(), m_window->get_height());
		Renderer::set_clear_color({ 0.0f, 0.0f, 0.0f, 1.0f });

		ImGuiRenderer::init();
	}

	Application::~Application(void)
	{
		Renderer::shutdown();

		m_layer->on_detach();
		delete m_layer;
	}

	void Application::push_layer(Layer *layer)
	{
		m_layer = layer;
		m_layer->on_attach();
	}

    void Application::close(void)
    {
		m_isRunning = false;
    }

	void Application::on_event(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(EN_BIND_EVENT(Application::on_window_close));

		if (e.handled)
			return;

		m_layer->on_event(e);
	}

	bool Application::on_window_close(WindowCloseEvent &e)
	{
		m_isRunning = false;
		return true;
	}

	void Application::run(void)
	{
		float timeSinceLastUpdate = 0.0f;

		while (m_isRunning)
		{
			float time = (float)glfwGetTime();
			float timestep = time - timeSinceLastUpdate;
			timeSinceLastUpdate = time;

			m_layer->on_update(timestep);

			Renderer::clear();

			m_layer->on_render();

			ImGuiRenderer::begin();
			m_layer->on_imgui_render();
			ImGuiRenderer::end();

			m_window->update();
		}
	}

}