#pragma once

#include <GLFW/glfw3.h>

#include <functional>
#include <cstdint>
#include <string>
#include <memory>

namespace Engine
{
	class Event;

	class Window
	{
	private:
		using EventCallback = std::function<void(Event &)>;

		struct WindowData
		{
			EventCallback eventCallback;

			GLFWwindow *windowHandle;
			std::string name;
			uint16_t width;
			uint16_t height;

			WindowData(const std::string &name, uint16_t width, uint16_t height) :
				windowHandle(nullptr),
				name(name),
				width(width),
				height(height)
			{

			}
		};
	
		WindowData m_windowData;

	public:
		Window(const WindowData &data);
		~Window(void);

		void update(void);

		inline void set_event_callback(const EventCallback &callback) { m_windowData.eventCallback = callback; }
		inline GLFWwindow * get_window_handle(void) const { return m_windowData.windowHandle; }
		inline uint16_t get_width(void) const { return m_windowData.width; }
		inline uint16_t get_height(void) const { return m_windowData.height; }

		static std::unique_ptr<Window> create(const std::string &name, uint16_t width = 800, uint16_t height = 600);
	};

}