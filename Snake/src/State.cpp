#include "State.h"
#include "StateManager.h"

State::State(StateManager &stateManager, Context context) :
	m_stateManager(&stateManager),
	m_context(context)
{

}

State::~State(void)
{

}

void State::push_state(ID stateID)
{
	m_stateManager->push_state(stateID);
}

void State::pop_state(void)
{
	m_stateManager->pop_state();
}