#pragma once

#include "../State.h"
#include "../../Graphics/TextRenderer.h"

class InputManager;

class MenuState : public State
{
private:
	InputManager &m_inputManager;
	TextRenderer m_textRenderer;

public:
	MenuState(StateManager &stateManager, Context context);
	virtual ~MenuState(void);

	virtual void draw(void) const override;
	virtual void imgui_render(void) const override;
	virtual bool update(float timestep) override;
	virtual bool handle_input(void) override;
};