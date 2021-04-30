#pragma once

#include "State.h"

#include <Engine/Graphics/Sprite.h>
#include <Engine/Graphics/TextRenderer.h>

class GameoverState : public State
{
private:
	Engine::TextRenderer m_textRenderer;

private:
	static const float BG_SCROLL_VELOCITY;

	Engine::Sprite m_replayButton;
	Engine::Sprite m_exitButton;
	std::shared_ptr<Engine::Texture> m_overlay;
	std::shared_ptr<Engine::Texture> m_background;
	float m_bgHorizontalPos1;
	float m_bgHorizontalPos2;

public:
	GameoverState(StateManager &stateManager, Context context);
	virtual ~GameoverState(void);

	virtual void render(void) const override;
	virtual void imgui_render(void) const override;
	virtual bool update(float timestep) override;
	virtual bool handle_input(void) override;
};