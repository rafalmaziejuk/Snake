#include "Engine/Core/Window.h"
#include "Engine/Core/EngineAssert.h"
#include "Engine/Events/Event.h"

#include <glad/glad.h>

namespace Engine
{
	Window::Window(const WindowData &data) :
		m_windowData(data.name, data.width, data.height)
	{
		{
			int result = glfwInit();
			EN_ASSERT(result);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_RESIZABLE, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_windowData.windowHandle = glfwCreateWindow(m_windowData.width, m_windowData.height, m_windowData.name.c_str(), nullptr, nullptr);
		EN_ASSERT(m_windowData.windowHandle);

		glfwMakeContextCurrent(m_windowData.windowHandle);
		glfwSwapInterval(1);

		{
			int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			EN_ASSERT(result);
		}

		glfwSetWindowUserPointer(m_windowData.windowHandle, &m_windowData);

		glfwSetWindowCloseCallback(m_windowData.windowHandle, [](GLFWwindow *window)
		{
			auto data = (WindowData *)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data->eventCallback(event);
		});
	}

	Window::~Window(void)
	{
		glfwDestroyWindow(m_windowData.windowHandle);
		glfwTerminate();
	}
	
	void Window::update(void)
	{
		glfwPollEvents();
		glfwSwapBuffers(m_windowData.windowHandle);
	}

	std::unique_ptr<Window> Window::create(const std::string &name, uint16_t width, uint16_t height)
	{
		return std::make_unique<Window>(WindowData(name, width, height));
	}

}