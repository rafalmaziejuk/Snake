#pragma once

#include "State.h"

class GameoverState : public State
{
private:


public:
	GameoverState(StateManager &stateManager, Context context);
	virtual ~GameoverState(void);

	virtual void draw(void) const override;
	virtual bool update(float timestep) override;
	virtual bool handle_input(void) override;
};