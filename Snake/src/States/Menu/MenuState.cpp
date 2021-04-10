#include "MenuState.h"
#include "../../Utils/InputManager.h"
#include "../../Utils/ImGui/ImGuiRenderer.h"

#include <GLFW/glfw3.h>

#include <sstream>

MenuState::MenuState(StateManager &stateManager, Context context) :
	State(stateManager, context),
	m_textRenderer(context.m_windowWidth, context.m_windowHeight),
	m_inputManager(InputManager::get_instance())
{
	m_textRenderer.load("assets/fonts/arial.ttf", 24);
}

MenuState::~MenuState(void)
{

}

void MenuState::draw(void) const
{
	std::stringstream ss;
	ss << "Press Enter to play!";
	m_textRenderer.render_text(ss.str(), { 295.0f, 275.0f }, 1.0f);
}

void MenuState::imgui_render(void) const
{

}

bool MenuState::update(float timestep)
{
	return true;
}

bool MenuState::handle_input(void)
{
	if (m_inputManager.is_key_pressed(GLFW_KEY_ENTER))
	{
		pop_state();
		push_state(ID::GAME_STATE);
	}

	return true;
}