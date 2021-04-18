#include "Snake.h"

#include "../../Graphics/Renderer.h"
#include "../../Graphics/Texture.h"

#include <GLFW/glfw3.h>

Snake::Snake(uint16_t windowWidth, uint16_t windowHeight) :
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_segmentTexture(Texture::create("assets/textures/snake_segment.png"))
{
	for (uint8_t i = 0; i < INIT_SNAKE_LENGTH; i++)
		add_segment({ windowWidth / 2, windowHeight / 2 });
}

void Snake::add_segment(const glm::vec2 &position)
{
	Sprite sprite(m_segmentTexture, position, { 32.0f, 32.0f });
	m_segments.push_back(sprite);
}

void Snake::draw(void) const
{
	for (auto &segment : m_segments)
		Renderer::draw(segment.m_sprite);
}

void Snake::update(float timestep)
{
	auto &headSprite = m_segments.begin()->m_sprite;
	glm::vec2 headVector;

	headVector.x =  cosf(glm::radians(90.0f - headSprite.get_angle())) * VELOCITY;
	headVector.y = -sinf(glm::radians(90.0f - headSprite.get_angle())) * VELOCITY;
	m_segments.begin()->move(headVector);

	for (auto it = m_segments.begin() + 1; it != m_segments.end(); it++)
	{
		auto &currentPosition = it->m_sprite.get_position();
		auto &previousPosition = (it - 1)->m_sprite.get_position();

		float distance = glm::distance(currentPosition, previousPosition);

		float a = currentPosition.x - previousPosition.x;
		float b = currentPosition.y - previousPosition.y;
		float angle = glm::degrees(atan2(b, a)) - 90.0f;
		it->m_sprite.set_angle(angle);

		if (distance > SPACING)
			it->move({ sinf(glm::radians(angle)) * (distance - SPACING), -cosf(glm::radians(angle)) * (distance - SPACING) });
	}
}

bool Snake::check_collision(void) const
{
	auto &headPosition = m_segments.begin()->m_sprite.get_position();

	if (headPosition.x < 0.0f || headPosition.x > static_cast<float>(m_windowWidth) ||
		headPosition.y < 0.0f || headPosition.y > static_cast<float>(m_windowHeight))
		return true;

	if (m_segments.size() > INIT_SNAKE_LENGTH)
	{
		for (auto it = m_segments.begin() + INIT_SNAKE_LENGTH; it != m_segments.end(); it++)
		{
			if (glm::distance(headPosition, it->m_sprite.get_position()) < COLLISION_DISTANCE)
				return true;
		}
	}

	return false;
}

bool Snake::check_collision_with_food(const Food &food)
{
	auto &foodPosition = food.m_sprite.get_position();
	auto &headPosition = m_segments.begin()->m_sprite.get_position();

	if (glm::distance(headPosition, foodPosition) < COLLISION_DISTANCE)
		return true;

	return false;
}

void Snake::extend(void)
{
	auto &tailPosition = (m_segments.end() - 1)->m_sprite.get_position();
	add_segment(tailPosition);
}

Food::Food(void) :
	m_sprite(Texture::create("assets/textures/food.png"))
{
	m_sprite.set_size({ 32.0f, 32.0f });
}

void Food::draw(void) const
{
	Renderer::draw(m_sprite);
}

void Food::update(void)
{
	float angle = sinf(static_cast<float>(glfwGetTime()));
	float scale = glm::clamp(angle, 0.60f, 0.65f);
	m_sprite.set_angle(glm::degrees(angle));
	m_sprite.set_scale(scale);
}

void Food::reset_position(const Snake &snake)
{
	//TODO: change to window size
	m_sprite.set_position
	(
		{ 
			static_cast<float>(rand() % 800) * 0.8f + 800.0f * 0.1f,
			static_cast<float>(rand() % 600) * 0.8f + 600.0f * 0.1f 
		}
	);
}