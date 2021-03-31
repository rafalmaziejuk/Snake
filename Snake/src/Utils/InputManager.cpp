#include "InputManager.h"

InputManager * InputManager::m_instance = nullptr;

InputManager & InputManager::get_instance(void)
{
	if (m_instance == nullptr)
		m_instance = new InputManager();

	return *m_instance;
}