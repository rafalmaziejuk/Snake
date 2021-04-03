#include "Snake.h"

#include "../../Utils/ResourceManager.h"
#include "../../Graphics/SpriteRenderer.h"

const float Snake::SEGMENT_SIZE = 20.0f;

Snake::Snake(void) :
	m_velocity(200.0f),
	m_direction()
{
	add_segment({ 400.0f, 300.0f });
}

void Snake::draw(const SpriteRenderer &spriteRenderer) const
{
	for (auto &segment : m_segments)
		spriteRenderer.draw(segment.m_sprite);
}

void Snake::update(float timestep)
{
	auto &head = m_segments[0];
	head.move({ timestep * m_velocity * m_direction.x, timestep * m_velocity * m_direction.y });
}

void Snake::add_segment(const glm::vec2 &position)
{
	m_segments.push_back(Sprite(ResourceManager::get_instance().get_texture("segment"), position, { SEGMENT_SIZE, SEGMENT_SIZE }));
}