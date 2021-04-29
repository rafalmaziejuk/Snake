#pragma once

#include "Engine/Core/Window.h"

int main(void);

namespace Engine
{
	class WindowCloseEvent;

	class Application
	{
	private:
		static Application *appInstance;
		friend int ::main(void);

		Application(const Application &app) = delete;
		Application & operator=(const Application &app) = delete;

	private:
		std::unique_ptr<Window> m_window;
		bool m_isRunning = true;

	private:
		bool on_window_close(WindowCloseEvent &e);
		void run(void);

	public:
		Application(const std::string &name);
		virtual ~Application(void);

		void close(void);
		Window & get_window(void) { return *m_window; }
		static Application & get(void) { return *appInstance; }

		void on_event(Event &e);
		virtual void on_update(float timestep) {  }
		virtual void on_render(void) {  }
		virtual void on_imgui_render(void) {  }
	};

	Application * create_application(void);

}