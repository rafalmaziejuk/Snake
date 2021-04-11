#pragma once

#include <glm/vec2.hpp>

class InputManager
{
private:
	InputManager(void) = default;
	InputManager(const InputManager &manager) = delete;
	InputManager & operator=(const InputManager &manager) = delete;

public:
	inline static InputManager & get_instance(void)
	{
		static InputManager instance;
		return instance;
	}

private:
	bool m_keys[1024]{ };
	bool m_processedKeys[1024]{ };
	double m_mouseX;
	double m_mouseY;

public:
	inline void key_press(int key) { m_keys[key] = true; }
	inline void key_process(int key) { m_processedKeys[key] = true; }
	inline void key_release(int key) { m_keys[key] = false; m_processedKeys[key] = false; }

	inline bool is_key_pressed(int key) const { return m_keys[key]; }
	inline bool is_key_processed(int key) const { return m_processedKeys[key]; }
	inline bool is_key_released(int key) const { return m_keys[key]; }

	inline void mouse_move(double x, double y)
	{
		m_mouseX = x;
		m_mouseY = y;
	}

	inline glm::vec2 get_mouse_position(void) const
	{
		return { static_cast<float>(m_mouseX), static_cast<float>(m_mouseY) };
	}
};