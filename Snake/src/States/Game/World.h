#pragma once

#include "Snake.h"
#include "../../Graphics/Sprite.h"

#include <memory>

class InputManager;

class World
{
private:
	static const float ROTATION_VELOCITY;

private:
	Sprite m_background;

private:
	InputManager &m_inputManager;

private:
	uint16_t m_windowWidth;
	uint16_t m_windowHeight;

private:
	Snake m_snake;
	Food m_food;
	bool m_isPlayerAlive;
	uint16_t m_playerScore;

public:
	World(uint16_t windowWidth, uint16_t windowHeight);

	void draw(void) const;
	void update(float timestep);
	void handle_input(void);

	inline bool is_player_alive(void) const { return m_isPlayerAlive; }
};