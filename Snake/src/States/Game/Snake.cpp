#include "Snake.h"

#include "../../Utils/ImGui/ImGuiRenderer.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Texture.h"

const float Snake::SEGMENT_SIZE = 25.0f;

Snake::Snake(uint16_t windowWidth, uint16_t windowHeight) :
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_segmentTexture(Texture::create_texture("assets/textures/test.png"))
{
	for (uint8_t i = 0; i < INIT_SNAKE_LENGTH; i++)
		add_segment({ 400.0f, 300.0f });
}

void Snake::add_segment(const glm::vec2 &position)
{
	m_segments.push_back(Sprite(m_segmentTexture, position, { SEGMENT_SIZE, SEGMENT_SIZE }));
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
			if (glm::distance(headPosition, it->m_sprite.get_position()) < SEGMENT_SIZE)
				return true;
		}
	}

	return false;
}

bool Snake::check_collision_with_food(const Food &food)
{
	auto &foodPosition = food.m_sprite.get_position();
	auto &headPosition = m_segments.begin()->m_sprite.get_position();

	if (glm::distance(headPosition, foodPosition) < SEGMENT_SIZE)
		return true;

	return false;
}

void Snake::extend(void)
{
	auto &tailPosition = (m_segments.end() - 1)->m_sprite.get_position();
	add_segment(tailPosition);
}

Food::Food(void) :
	m_sprite(Texture::create_texture("assets/textures/test.png"))
{
	m_sprite.set_size({ Snake::SEGMENT_SIZE, Snake::SEGMENT_SIZE });
}

void Food::draw(void) const
{
	Renderer::draw(m_sprite);
}

void Food::reset_position(const Snake &snake)
{
	m_sprite.set_position({ static_cast<float>(rand() % snake.m_windowWidth) * 0.8f + static_cast<float>(snake.m_windowWidth) * 0.1f,
							static_cast<float>(rand() % snake.m_windowHeight) * 0.8f + static_cast<float>(snake.m_windowHeight) * 0.1f });
}