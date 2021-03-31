#include "Application.h"
#include "States/StateIdentifiers.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cassert>

const float Application::TIME_PER_FRAME = 1.0f / 60.0f;

static void resize_callback(GLFWwindow *window, GLint width, GLint height)
{
	glViewport(0, 0, width, height);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	
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

	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
	glViewport(0, 0, m_width, m_height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	//register_states();
	//m_stateManager.add_state(ID::MENU_STATE);
}

Application::~Application(void)
{
	glfwTerminate();
}

void Application::register_states(void)
{
	/*m_stateManager.register_state<MenuState>(ID::MENU_STATE);
	m_stateManager.register_state<GameState>(ID::MENU_STATE);
	m_stateManager.register_state<GameoverState>(ID::MENU_STATE);*/
}

void Application::run(void)
{
	float timeSinceLastUpdate = 0.0f;

	while (!glfwWindowShouldClose(m_window))
	{
		float elapsedTime = (float)glfwGetTime() - m_lastFrameTime;
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			glfwPollEvents();
			//input
			//m_stateManager.update(m_timestep);

			//if (m_stateManager.is_empty())
				//glfwSetWindowShouldClose(m_window, 1);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		//m_stateManager.render();
		glfwSwapBuffers(m_window);
	}
}