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
	static const float ROTATION_SPEED;
	static const float SPACING;

private:
	struct Segment
	{
		Sprite m_sprite;

		Segment(const Sprite &sprite) :
			m_sprite(sprite)
		{

		}

		void move(const glm::vec2 &position)
		{
			glm::vec2 newPosition(m_sprite.get_position());
			newPosition.x += position.x;
			newPosition.y += position.y;

			m_sprite.set_position(newPosition);
		}
		
		inline void rotate(float angle)
		{
			m_sprite.set_angle(m_sprite.get_angle() + angle);
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
		direction ? m_segments.begin()->rotate(ROTATION_SPEED) : m_segments.begin()->rotate(-ROTATION_SPEED);
	}
};