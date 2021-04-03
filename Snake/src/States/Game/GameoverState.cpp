#include "GameoverState.h"

GameoverState::GameoverState(StateManager &stateManager, Context context) :
	State(stateManager, context)
{

}

GameoverState::~GameoverState(void)
{

}

void GameoverState::draw(void) const
{

}

bool GameoverState::update(float timestep)
{
	return true;
}

bool GameoverState::handle_input(void)
{
	return true;
}