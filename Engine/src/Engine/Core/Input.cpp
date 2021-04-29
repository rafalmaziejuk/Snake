#include "Engine/Core/Input.h"
#include "Engine/Core/Application.h"

namespace Engine
{

	bool Input::is_key_pressed(KeyCode key)
	{
		auto* window = static_cast<GLFWwindow*>(Application::get().get_window().get_window_handle());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::is_mouse_button_pressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow *>(Application::get().get_window().get_window_handle());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::get_mouse_position(void)
	{
		auto* window = static_cast<GLFWwindow*>(Application::get().get_window().get_window_handle());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

}