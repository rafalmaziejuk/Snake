#pragma once

#include "../../Graphics/Sprite.h"

#include <glm/glm.hpp>

#include <vector>

class SpriteRenderer;
class Food;

class Snake
{
private:
	static const float SEGMENT_SIZE;
	const float SPACING = 20.0f;
	const float VELOCITY = 5.0f;
	const float ROTATION_SPEED = 5.0f;
	const uint8_t INIT_SNAKE_LENGTH = 10;

private:
	std::shared_ptr<Texture> m_segmentTexture;

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
			m_sprite.rotate(angle);
		}
	};

private:
	std::vector<Segment> m_segments;
	uint16_t m_windowWidth;
	uint16_t m_windowHeight;

private:
	void add_segment(const glm::vec2 &position);

public:
	Snake(uint16_t windowWidth, uint16_t windowHeight);

	inline void change_direction(bool direction)
	{
		direction ? m_segments.begin()->rotate(ROTATION_SPEED) : m_segments.begin()->rotate(-ROTATION_SPEED);
	}

	void draw(void) const;
	void update(float timestep);

	bool check_collision(void) const;
	bool check_collision_with_food(const Food &food);
	void extend(void);

	friend class Food;
};

class Food
{
private:
	Sprite m_sprite;

public:
	Food(void);

	void draw(void) const;
	void reset_position(const Snake &snake);

	friend class Snake;
};