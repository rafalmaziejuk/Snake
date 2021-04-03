#pragma once

#include "../../Graphics/Sprite.h"

#include <glm/glm.hpp>

#include <vector>

class SpriteRenderer;

class Snake
{
private:
	static const float SEGMENT_SIZE;
	static const float VELOCITY_SCALAR;

private:
	struct Segment
	{
		Sprite m_sprite;

		Segment(const Sprite &sprite) :
			m_sprite(sprite)
		{

		}

		void move(void)
		{
			glm::vec2 position(m_sprite.get_position());
			glm::vec2 newPosition;

			newPosition.x = position.x +  cosf(glm::radians(90.0f - m_sprite.get_angle())) * VELOCITY_SCALAR;
			newPosition.y = position.y + -sinf(glm::radians(90.0f - m_sprite.get_angle())) * VELOCITY_SCALAR;

			m_sprite.set_position(newPosition);
		}
		
		inline void rotate(float angle)
		{
			m_sprite.rotate(angle);
		}
	};

private:
	std::vector<Segment> m_segments;

private:
	void add_segment(const glm::vec2 &position);

public:
	Snake(void);

	void draw(const SpriteRenderer &spriteRenderer) const;
	void update(float timestep);

	inline void change_direction(bool direction) 
	{ 
		direction ? m_segments.begin()->rotate(5.0f) : m_segments.begin()->rotate(-5.0f);
	}
};