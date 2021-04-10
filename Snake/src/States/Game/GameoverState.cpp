#include "GameoverState.h"
#include "../../Utils/InputManager.h"
#include "../../Utils/ImGui/ImGuiRenderer.h"

#include <GLFW/glfw3.h>

#include <sstream>

GameoverState::GameoverState(StateManager &stateManager, Context context) :
	State(stateManager, context),
	m_textRenderer(context.m_windowWidth, context.m_windowHeight),
	m_inputManager(InputManager::get_instance())
{
	m_textRenderer.load("assets/fonts/arial.ttf", 24);
}

GameoverState::~GameoverState(void)
{

}

void GameoverState::draw(void) const
{
	std::stringstream ss;
	
	ss << "Do you want to play again? Press Enter!";
	m_textRenderer.render_text(ss.str(), { 185.0f, 275.0f }, 1.0f);
	ss.str(std::string());
	ss << "Do you want to exit? Press Escape!";
	m_textRenderer.render_text(ss.str(), { 185.0f, 300.0f }, 1.0f);
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