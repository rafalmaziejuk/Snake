#include "GameState.h"

GameState::GameState(StateManager &stateManager, Context context) :
	State(stateManager, context)
{

}

GameState::~GameState(void)
{

}

void GameState::draw(void) const
{

}

bool GameState::update(float timestep)
{
	return true;
}

bool GameState::handle_input(void)
{
	return true;
}