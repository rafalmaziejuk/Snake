#pragma once

#include "../State.h"
#include "World.h"

class GameState : public State
{
private:
	World m_world;

public:
	GameState(StateManager &stateManager, Context context);
	virtual ~GameState(void);

	virtual void draw(void) const override;
	virtual void imgui_render(void) const override;
	virtual bool update(float timestep) override;
	virtual bool handle_input(void) override;
};