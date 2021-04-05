#pragma once

#include "../State.h"
#include "../../Graphics/TextRenderer.h"

class InputManager;

class GameoverState : public State
{
private:
	InputManager &m_inputManager;
	TextRenderer m_textRenderer;

public:
	GameoverState(StateManager &stateManager, Context context);
	virtual ~GameoverState(void);

	virtual void draw(void) const override;
	virtual bool update(float timestep) override;
	virtual bool handle_input(void) override;
};