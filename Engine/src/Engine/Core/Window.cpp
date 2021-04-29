#include "Engine/Core/Window.h"
#include "Engine/Core/EngineAssert.h"

#include <glad/glad.h>

namespace Engine
{

	Window::Window(const std::string &name, uint16_t width, uint16_t height) :
		m_windowHandle(nullptr),
		m_width(width),
		m_height(height)
	{
		{
			int result = glfwInit();
			EN_ASSERT(result);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_RESIZABLE, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_windowHandle = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);
		EN_ASSERT(m_windowHandle);

		glfwMakeContextCurrent(m_windowHandle);
		glfwSwapInterval(1);

		{
			int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			EN_ASSERT(result);
		}
	}

	Window::~Window(void)
	{
		glfwDestroyWindow(m_windowHandle);
		glfwTerminate();
	}

	void Window::update(void)
	{
		glfwPollEvents();
		glfwSwapBuffers(m_windowHandle);
	}

	std::unique_ptr<Window> Window::create(const std::string &name, uint16_t width, uint16_t height)
	{
		return std::make_unique<Window>(name, width, height);
	}

}