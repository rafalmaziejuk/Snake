#pragma once

#include "State.h"

#include <Engine/Graphics/Sprite.h>

class MenuState : public State
{
private:
	static const float BG_SCROLL_VELOCITY;

	Engine::Sprite m_playButton;
	Engine::Sprite m_exitButton;
	std::shared_ptr<Engine::Texture> m_overlay;
	std::shared_ptr<Engine::Texture> m_background;
	float m_bgHorizontalPos1;
	float m_bgHorizontalPos2;

public:
	MenuState(StateManager &stateManager, Context context);
	virtual ~MenuState(void);

	virtual void render(void) const override;
	virtual void imgui_render(void) const override;
	virtual bool update(float timestep) override;
	virtual bool handle_input(void) override;
};