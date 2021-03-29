#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cassert>

namespace Snake
{

	static void resize_callback(GLFWwindow *window, GLint width, GLint height)
	{
		glViewport(0, 0, width, height);
	}

	static void handle_input(GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	Application::Application(const std::string &name, uint16_t width, uint16_t height) :
		m_window(nullptr),
		m_name(name),
		m_width(width),
		m_height(height)
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
	}

	Application::~Application(void)
	{
		glfwTerminate();
	}

	void Application::run(void)
	{
		while (!glfwWindowShouldClose(m_window))
		{
			float time = (float)glfwGetTime();
			m_timestep = time - m_lastFrameTime;
			m_lastFrameTime = time;

			glfwPollEvents();
			handle_input(m_window);
			//update

			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//render

			glfwSwapBuffers(m_window);
		}
	}

}