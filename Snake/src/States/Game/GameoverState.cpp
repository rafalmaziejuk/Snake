#include "GameoverState.h"
#include "../../Utils/InputManager.h"
#include "../../Utils/ImGui/ImGuiRenderer.h"

#include <GLFW/glfw3.h>

GameoverState::GameoverState(StateManager &stateManager, Context context) :
	State(stateManager, context),
	m_inputManager(InputManager::get_instance())
{

}

GameoverState::~GameoverState(void)
{

}

void GameoverState::draw(void) const
{
	
}

void GameoverState::imgui_render(void) const
{

}

bool GameoverState::update(float timestep)
{
	return true;
}

bool GameoverState::handle_input(void)
{
	if (m_inputManager.is_key_pressed(GLFW_KEY_ENTER))
	{
		pop_state();
		push_state(ID::GAME_STATE);
	}

	if (m_inputManager.is_key_pressed(GLFW_KEY_ESCAPE))
		pop_state();

	return true;
}