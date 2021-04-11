#include "Application.h"
#include "Utils/ImGui/ImGuiRenderer.h"
#include "Utils/InputManager.h"
#include "Graphics/Renderer.h"
#include "States/StateIdentifiers.h"
#include "States/Menu/MenuState.h"
#include "States/Game/GameState.h"
#include "States/Game/GameoverState.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <cassert>
#include <ctime>

static void resize_callback(GLFWwindow *window, GLint width, GLint height)
{
	glViewport(0, 0, width, height);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	switch (action)
	{
		case GLFW_PRESS:
			InputManager::get_instance().key_press(key);
			break;

		case GLFW_RELEASE:
			InputManager::get_instance().key_release(key);
			break;
	}
}

static void cursor_position_callback(GLFWwindow *window, double x, double y)
{
	InputManager::get_instance().mouse_move(x, y);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
	switch (action)
	{
		case GLFW_PRESS:
			InputManager::get_instance().key_press(button);
			break;

		case GLFW_RELEASE:
			InputManager::get_instance().key_release(button);
			break;
	}
}

Application::Application(const std::string &name, uint16_t width, uint16_t height) :
	m_window(nullptr),
	m_name(name),
	m_windowWidth(width),
	m_windowHeight(height),
	m_stateManager(State::Context(width, height))
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	assert(glfwInit());

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, name.c_str(), nullptr, nullptr);
	assert(m_window);

	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, resize_callback);
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSwapInterval(1);

	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	ImGuiRenderer::init(m_window);
	Renderer::init(m_windowWidth, m_windowHeight);
	Renderer::set_viewport(m_windowWidth, m_windowHeight);
	Renderer::set_clear_color({ 0.0f, 0.0f, 0.0f, 1.0f });

	register_states();
	m_stateManager.push_state(ID::MENU_STATE);
}

Application::~Application(void)
{
	ImGuiRenderer::shutdown();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Application::register_states(void)
{
	m_stateManager.register_state<MenuState>(ID::MENU_STATE);
	m_stateManager.register_state<GameState>(ID::GAME_STATE);
	m_stateManager.register_state<GameoverState>(ID::GAMEOVER_STATE);
}

void Application::run(void)
{
	float timeSinceLastUpdate = 0.0f;

	while (!glfwWindowShouldClose(m_window))
	{
		float time = (float)glfwGetTime();
		float timestep = time - timeSinceLastUpdate;
		timeSinceLastUpdate = time;

		glfwPollEvents();
		m_stateManager.handle_input();
		m_stateManager.update(timestep);

		if (m_stateManager.is_empty())
			glfwSetWindowShouldClose(m_window, 1);

		m_renderer->clear();

		m_stateManager.draw();
		ImGuiRenderer::begin();
		m_stateManager.imgui_render();
		ImGuiRenderer::end(m_windowWidth, m_windowHeight);

		glfwSwapBuffers(m_window);
	}
}