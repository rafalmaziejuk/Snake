#pragma once

#include "StateIdentifiers.h"

class StateManager;

class State
{
public:
	struct Context
	{
		uint16_t m_windowWidth;
		uint16_t m_windowHeight;

		Context(uint16_t windowWidth, uint16_t windowHeight) :
			m_windowWidth(windowWidth),
			m_windowHeight(windowHeight)
		{

		}
	};

private:
	Context m_context;
	StateManager *m_stateManager;

protected:
	inline Context get_context(void) const 
	{ 
		return m_context;
	}

	void push_state(ID stateID);
	void pop_state(void);

public:
	State(StateManager &stateManager, Context context);
	virtual ~State(void);

	virtual void draw(void) const = 0;
	virtual bool update(float timestep) = 0;
	virtual bool handle_input(void) = 0;
};