#pragma once

#include "../State.h"

#include <memory>

class InputManager;
class Texture;

class MenuState : public State
{
private:
	static const float BG_SCROLL_VELOCITY;

private:
	InputManager &m_inputManager;

private:
	std::shared_ptr<Texture> m_menu;
	std::shared_ptr<Texture> m_background;
	float m_bgHorizontalPos1;
	float m_bgHorizontalPos2;

public:
	MenuState(StateManager &stateManager, Context context);
	virtual ~MenuState(void);

	virtual void draw(void) const override;
	virtual void imgui_render(void) const override;
	virtual bool update(float timestep) override;
	virtual bool handle_input(void) override;
};