#include "Snake.h"

#include "../../Utils/ResourceManager.h"
#include "../../Utils/ImGui/ImGuiRenderer.h"
#include "../../Graphics/SpriteRenderer.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

const float Snake::SEGMENT_SIZE = 25.0f;
const float Snake::VELOCITY_SCALAR = 5.0f;
const float Snake::ROTATION_SPEED = 5.0f;
const float Snake::SPACING = 20.0f;

Snake::Snake(void)
{
	add_segment({ 400.0f, 300.0f });
	add_segment({ 400.0f, 300.0f });
	add_segment({ 400.0f, 300.0f });
	add_segment({ 400.0f, 300.0f });
}

void Snake::draw(const SpriteRenderer &spriteRenderer) const
{
	for (auto &segment : m_segments)
		spriteRenderer.draw(segment.m_sprite);
}

void Snake::update(float timestep)
{
	auto head = m_segments.begin();
	glm::vec2 headVector;

	headVector.x =  cosf(glm::radians(90.0f - head->m_sprite.get_angle())) * VELOCITY_SCALAR;
	headVector.y = -sinf(glm::radians(90.0f - head->m_sprite.get_angle())) * VELOCITY_SCALAR;
	head->move(headVector);

	for (auto it = m_segments.begin() + 1; it != m_segments.end(); it++)
	{
		auto currentPosition = it->m_sprite.get_position();
		auto previousPosition = (it - 1)->m_sprite.get_position();

		float distance = 
		sqrtf
		(
			powf(abs(currentPosition.x - previousPosition.x), 2.0f) +
			powf(abs(currentPosition.y - previousPosition.y), 2.0f)
		);

		float a = currentPosition.x - previousPosition.x;
		float b = currentPosition.y - previousPosition.y;
		float angle = glm::degrees(atan2(b, a)) - 90.0f;
		it->m_sprite.set_angle(angle);

		if (distance > SPACING)
			it->move({ sinf(glm::radians(angle)) * (distance - SPACING), -cosf(glm::radians(angle)) * (distance - SPACING) });
	}
}

void Snake::add_segment(const glm::vec2 &position)
{
	m_segments.push_back(Sprite(ResourceManager::get_instance().get_texture("segment"), position, { SEGMENT_SIZE, SEGMENT_SIZE }));
}