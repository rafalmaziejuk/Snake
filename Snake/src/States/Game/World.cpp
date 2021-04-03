#include "World.h"
#include "../../Graphics/SpriteRenderer.h"
#include "../../Utils/InputManager.h"

#include <GLFW/glfw3.h>

World::World(uint16_t windowWidth, uint16_t windowHeight) :
	m_spriteRenderer(SpriteRenderer::get_instance()),
	m_inputManager(InputManager::get_instance()),
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight)
{

}

void World::draw(void) const
{
	m_snake.draw(m_spriteRenderer);
}

void World::update(float timestep)
{
	m_snake.update(timestep);
}

void World::handle_input(void)
{
	if (m_inputManager.is_key_pressed(GLFW_KEY_A))
	{
		m_snake.change_direction(false);
		m_inputManager.key_process(GLFW_KEY_A);
	}

	if (m_inputManager.is_key_pressed(GLFW_KEY_D))
	{
		m_snake.change_direction(true);
		m_inputManager.key_process(GLFW_KEY_D);
	}
}