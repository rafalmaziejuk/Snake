#pragma once

#include "../../Graphics/Sprite.h"

#include <glm/vec2.hpp>

#include <vector>

class SpriteRenderer;

class Snake
{
private:
	static const float SEGMENT_SIZE;

private:
	struct Segment
	{
		Sprite m_sprite;

		Segment(const Sprite &sprite) :
			m_sprite(sprite)
		{

		}

		void move(const glm::vec2 &vector)
		{
			glm::vec2 position(m_sprite.get_position());
			glm::vec2 newPosition(position.x + vector.x, position.y + vector.y);
			m_sprite.set_position(newPosition);
		}
	};

private:
	std::vector<Segment> m_segments;
	glm::vec2 m_direction;
	float m_velocity;

private:
	void add_segment(const glm::vec2 &position);

public:
	Snake(void);

	void draw(const SpriteRenderer &spriteRenderer) const;
	void update(float timestep);

	inline void change_direction(const glm::vec2 &direction) { m_direction = direction; }
};