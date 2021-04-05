#include "World.h"
#include "../../Graphics/SpriteRenderer.h"
#include "../../Utils/InputManager.h"

#include <GLFW/glfw3.h>
#include <sstream>

World::World(uint16_t windowWidth, uint16_t windowHeight) :
	m_spriteRenderer(SpriteRenderer::get_instance()),
	m_inputManager(InputManager::get_instance()),
	m_textRenderer(windowWidth, windowHeight),
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_snake(windowWidth, windowHeight),
	m_food(),
	m_isPlayerAlive(true),
	m_playerScore(0)
{
	m_textRenderer.load("assets/fonts/arial.ttf", 24);
	m_food.reset_position(m_snake);
}

void World::draw(void) const
{
	std::stringstream ss; 
	ss << m_playerScore;
	m_textRenderer.render_text(ss.str(), { static_cast<float>(m_windowWidth) - 30.0f, 5.0f }, 1.0f);

	m_snake.draw(m_spriteRenderer);
	m_food.draw(m_spriteRenderer);
}

void World::update(float timestep)
{
	m_snake.update(timestep);

	if (m_snake.check_collision())
		m_isPlayerAlive = false;

	if (m_snake.check_collision_with_food(m_food))
	{
		m_playerScore++;
		m_food.reset_position(m_snake);
		m_snake.extend();
	}
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