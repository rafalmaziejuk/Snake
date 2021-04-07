#include "Application.h"
#include "Utils/ImGui/ImGuiRenderer.h"
#include "Utils/InputManager.h"
#include "Graphics/SpriteRenderer.h"
#include "States/StateIdentifiers.h"
#include "States/Menu/MenuState.h"
#include "States/Game/GameState.h"
#include "States/Game/GameoverState.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

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

Application::Application(const std::string &name, uint16_t width, uint16_t height) :
	m_window(nullptr),
	m_name(name),
	m_width(width),
	m_height(height),
	m_stateManager(State::Context(width, height))
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	assert(glfwInit());

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, name.c_str(), nullptr, nullptr);
	assert(m_window);

	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, resize_callback);
	glfwSetKeyCallback(m_window, key_callback);
	glfwSwapInterval(1);

	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
	glViewport(0, 0, m_width, m_height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	register_states();
	m_stateManager.push_state(ID::MENU_STATE);

	ImGuiRenderer::init(m_window);
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

		glClear(GL_COLOR_BUFFER_BIT);

		m_stateManager.render();

		glfwSwapBuffers(m_window);
	}
}