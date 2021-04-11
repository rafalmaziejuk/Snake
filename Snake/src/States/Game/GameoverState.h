#pragma once

#include "../State.h"
#include "../../Graphics/Sprite.h"
#include "../../Graphics/TextRenderer.h"

#include <memory>

class InputManager;

class GameoverState : public State
{
private:
	InputManager &m_inputManager;
	TextRenderer m_textRenderer;

private:
	static const float BG_SCROLL_VELOCITY;

	Sprite m_replayButton;
	Sprite m_exitButton;
	std::shared_ptr<Texture> m_overlay;
	std::shared_ptr<Texture> m_background;
	float m_bgHorizontalPos1;
	float m_bgHorizontalPos2;

public:
	GameoverState(StateManager &stateManager, Context context);
	virtual ~GameoverState(void);

	virtual void draw(void) const override;
	virtual void imgui_render(void) const override;
	virtual bool update(float timestep) override;
	virtual bool handle_input(void) override;
};