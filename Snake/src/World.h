#pragma once

#include "Snake.h"

#include <Engine/Graphics/Sprite.h>
#include <Engine/Graphics/TextRenderer.h>

class World
{
private:
	static const float ROTATION_VELOCITY;

private:
	Engine::Sprite m_background;

private:
	Engine::TextRenderer m_textRenderer;

private:
	uint16_t m_windowWidth;
	uint16_t m_windowHeight;

private:
	Snake m_snake;
	Food m_food;
	bool m_isPlayerAlive;

public:
	World(uint16_t windowWidth, uint16_t windowHeight);

	void render(void) const;
	void update(float timestep);
	void handle_input(void);

	inline bool is_player_alive(void) const { return m_isPlayerAlive; }
};