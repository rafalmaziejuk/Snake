#include "GameState.h"

GameState::GameState(StateManager &stateManager, Context context) :
	State(stateManager, context),
	m_world(context.m_windowWidth, context.m_windowHeight)
{
}

GameState::~GameState(void)
{

}

void GameState::render(void) const
{
	m_world.render();
}

void GameState::imgui_render(void) const
{

}

bool GameState::update(float timestep)
{
	m_world.update(timestep);
	
	if (!m_world.is_player_alive())
	{
		pop_state();
		push_state(ID::GAMEOVER_STATE);
	}

	return true;
}

bool GameState::handle_input(void)
{
	m_world.handle_input();

	return true;
}