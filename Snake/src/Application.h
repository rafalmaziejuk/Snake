#pragma once

#include "Utils/ResourceManager.h"
#include "Utils/StateManager.h"

#include <GLFW/glfw3.h>

#include <string>
#include <cstdint>

class Application
{
private:
	GLFWwindow *m_window;
	std::string m_name;
	uint16_t m_width;
	uint16_t m_height;

private:
	StateManager m_stateManager;

private:
	Application(const Application &app) = delete;
	Application & operator=(const Application &app) = delete;

	void register_states(void);

public:
	Application(const std::string &name, uint16_t width, uint16_t height);
	~Application(void);

	void run(void);
};