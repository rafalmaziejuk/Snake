#include "World.h"
#include "../../Utils/InputManager.h"
#include "../../Graphics/Texture.h"
#include "../../Graphics/Renderer.h"

#include <GLFW/glfw3.h>

#include <sstream>

const float World::ROTATION_VELOCITY = 0.5f;
uint16_t playerScore;

World::World(uint16_t windowWidth, uint16_t windowHeight) :
	m_inputManager(InputManager::get_instance()),
	m_textRenderer(windowWidth, windowHeight),
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_background(Texture::create("assets/textures/game_bg.png")),
	m_snake(windowWidth, windowHeight),
	m_food(),
	m_isPlayerAlive(true)
{
	m_textRenderer.load("assets/fonts/EdgeOfTheGalaxyRegular.otf", 25);

	m_background.set_position({ static_cast<float>(m_windowWidth) / 2.0f, static_cast<float>(m_windowHeight) / 2.0f });
	m_food.reset_position(m_snake);
	playerScore = 0;
}

void World::draw(void) const
{
	Renderer::draw(m_background);
	m_snake.draw();
	m_food.draw();

	std::stringstream ss;
	if (playerScore < 10)
		ss << "00" << playerScore;
	else if (playerScore >= 10 && playerScore < 100)
		ss << "0" << playerScore;
	else
		ss << playerScore;

	m_textRenderer.render_text(ss.str(), { static_cast<float>(m_windowWidth) - 50.0f, 5.0f }, 1.0f);
}

void World::update(float timestep)
{
	m_background.rotate(timestep * ROTATION_VELOCITY);

	m_snake.update(timestep);
	m_food.update();

	if (m_snake.check_collision())
		m_isPlayerAlive = false;

	if (m_snake.check_collision_with_food(m_food))
	{
		playerScore++;
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