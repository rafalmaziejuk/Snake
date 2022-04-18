#pragma once

#include <Engine/Graphics/Sprite.h>

#include <glm/glm.hpp>

#include <vector>

class Food;

class Snake
{
private:
	const float COLLISION_DISTANCE = 16.0f;
	const float SPACING = 20.0f;
	const float VELOCITY = 2.0f;
	const float ROTATION_SPEED = 2.0f;
	const uint8_t INIT_SNAKE_LENGTH = 10;

private:
	std::shared_ptr<Engine::Texture> m_segmentTexture;

	struct Segment
	{
		Engine::Sprite m_sprite;

		Segment(const Engine::Sprite &sprite) :
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

	void render(void) const;
	void update(float timestep);

	bool check_collision(void) const;
	bool check_collision_with_food(const Food &food);
	void extend(void);
};

class Food
{
private:
	Engine::Sprite m_sprite;

public:
	Food(void);

	void render(void) const;
	void update(void);
	void reset_position(const Snake &snake);

	friend class Snake;
};