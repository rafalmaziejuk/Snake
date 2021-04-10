#include "StateManager.h"

#include <cassert>

StateManager::StateManager(State::Context context) :
	m_states(),
	m_stateConstructors(),
	m_pendingActions(),
	m_context(context)
{

}

std::unique_ptr<State> StateManager::create_state(ID stateID)
{
	auto stateConstructor = m_stateConstructors.find(stateID);
	assert(stateConstructor != m_stateConstructors.end());

	return stateConstructor->second();
}

void StateManager::do_pending_actions(void)
{
	for (auto &pendingAction : m_pendingActions)
	{
		switch (pendingAction.m_action)
		{
			case Action::ADD:
				m_states.push_back(create_state(pendingAction.m_stateID));
				break;

			case Action::DELETE:
				m_states.pop_back();
				break;
		}
	}

	m_pendingActions.clear();
}

void StateManager::draw(void)
{
	for (auto &state : m_states)
		state->draw();
}

void StateManager::imgui_render(void)
{
	for (auto &state : m_states)
		state->imgui_render();
}

void StateManager::update(float timestep)
{
	for (auto &state : m_states)
	{
		if (!state->update(timestep))
			break;
	}

	do_pending_actions();
}

void StateManager::handle_input(void)
{
	for (auto &state : m_states)
	{
		if (!state->handle_input())
			break;
	}

	do_pending_actions();
}

void StateManager::push_state(ID stateID)
{
	m_pendingActions.push_back(PendingAction(Action::ADD, stateID));
}

void StateManager::pop_state(void)
{
	m_pendingActions.push_back(PendingAction(Action::DELETE));
}

bool StateManager::is_empty(void) const
{
	return m_states.empty();
}

StateManager::PendingAction::PendingAction(Action action, ID stateID) :
	m_action(action),
	m_stateID(stateID)
{

}