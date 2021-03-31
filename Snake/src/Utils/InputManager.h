#pragma once

class InputManager
{
private:
	static InputManager *m_instance;

	InputManager(void) = default;
	InputManager(const InputManager & manager) = delete;
	InputManager & operator=(const InputManager & manager) = delete;

public:
	static InputManager & get_instance(void);

private:
	bool m_keys[1024]{ };
	bool m_processedKeys[1024]{ };

public:
	inline void key_press(int key) { m_keys[key] = true; }
	inline void key_process(int key) { m_processedKeys[key] = true; }
	inline void key_release(int key) { m_keys[key] = false; m_processedKeys[key] = false; }

	inline bool is_key_pressed(int key) const { return m_keys[key]; }
	inline bool is_key_processed(int key) const { return m_processedKeys[key]; }
	inline bool is_key_released(int key) const { return m_keys[key]; }
};