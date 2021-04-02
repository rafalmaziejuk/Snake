#include "Application.h"
#include "Utils/InputManager.h"
#include "States/StateIdentifiers.h"
#include "States/MenuState.h"
#include "States/GameState.h"
#include "States/GameoverState.h"

#include "Utils/ImGui/ImGuiRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cassert>

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

	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
	glViewport(0, 0, m_width, m_height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	register_states();
	m_stateManager.add_state(ID::GAME_STATE);

	ResourceManager::get_instance().load_texture("texture", "assets/textures/awesomeface.png");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_width), static_cast<float>(m_height), 0.0f, -1.0f, 1.0f);
	ResourceManager::get_instance().load_shader("sprite", "assets/shaders/sprite.vert", "assets/shaders/sprite.frag");

	auto spriteShader = ResourceManager::get_instance().get_shader("sprite");
	spriteShader->use();
	spriteShader->set_int("sprite", 0);
	spriteShader->set_mat4("projection", projection);

	m_spriteRenderer = new SpriteRenderer(spriteShader);

	ImGuiRenderer::init(m_window);
}

Application::~Application(void)
{
	delete m_spriteRenderer;
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

		
		ImGuiRenderer::begin();
		{
			ImGui::Begin("FPS");
			ImGui::Text("%.3f ms / %.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		ImGuiRenderer::end(m_width, m_height);

		m_spriteRenderer->draw(ResourceManager::get_instance().get_texture("texture"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f));
		m_stateManager.render();
		glfwSwapBuffers(m_window);
	}
}