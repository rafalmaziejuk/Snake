#pragma once

#include "State.h"

class GameState : public State
{
private:
	

public:
	GameState(StateManager &stateManager, Context context);
	virtual ~GameState(void);

	virtual void draw(void) const override;
	virtual bool update(float timestep) override;
	virtual bool handle_input(void) override;
};