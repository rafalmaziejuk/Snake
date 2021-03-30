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

void State::add_state(ID stateID)
{
	m_stateManager->add_state(stateID);
}

void State::delete_state(void)
{
	m_stateManager->delete_state();
}