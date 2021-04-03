#pragma once

#include "../State.h"

class MenuState : public State
{
private:


public:
	MenuState(StateManager &stateManager, Context context);
	virtual ~MenuState(void);

	virtual void draw(void) const override;
	virtual bool update(float timestep) override;
	virtual bool handle_input(void) override;
};