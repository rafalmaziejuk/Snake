#pragma once

#include <GLFW/glfw3.h>

#include <functional>
#include <cstdint>
#include <string>
#include <memory>

namespace Engine
{

	class Window
	{
	private:
		GLFWwindow *m_windowHandle;
		std::string m_name;
		uint16_t m_width;
		uint16_t m_height;

	public:
		Window(const std::string &name, uint16_t width, uint16_t height);
		~Window(void);

		void update(void);

		inline GLFWwindow * get_window_handle(void) const { return m_windowHandle; }
		inline uint16_t get_width(void) const { return m_width; }
		inline uint16_t get_height(void) const { return m_height; }

		static std::unique_ptr<Window> create(const std::string &name, uint16_t width = 800, uint16_t height = 600);
	};

}