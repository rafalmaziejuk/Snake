#include "MenuState.h"
#include "../../Utils/InputManager.h"
#include "../../Graphics/Texture.h"
#include "../../Graphics/Renderer.h"

#include <GLFW/glfw3.h>

const float MenuState::BG_SCROLL_VELOCITY = 25.0f;

MenuState::MenuState(StateManager &stateManager, Context context) :
	State(stateManager, context),
	m_inputManager(InputManager::get_instance()),
	m_menu(Texture::create_texture("assets/textures/menu.png")),
	m_background(Texture::create_texture("assets/textures/menu_bg.png")),
	m_bgHorizontalPos1(static_cast<float>(m_background->get_width()) / 2.0f),
	m_bgHorizontalPos2(-static_cast<float>(m_background->get_width()) / 2.0f)
{

}

MenuState::~MenuState(void)
{

}

void MenuState::draw(void) const
{
	Renderer::draw({ m_bgHorizontalPos1, get_context().m_windowHeight / 2 }, m_background);
	Renderer::draw({ m_bgHorizontalPos2, get_context().m_windowHeight / 2 }, m_background);
	Renderer::draw({ get_context().m_windowWidth / 2, get_context().m_windowHeight / 2 }, m_menu);
}

void MenuState::imgui_render(void) const
{
	
}

bool MenuState::update(float timestep)
{
	if (m_bgHorizontalPos1 >= static_cast<float>(get_context().m_windowWidth) + static_cast<float>(m_background->get_width()) / 2.0f)
		m_bgHorizontalPos1 = -static_cast<float>(get_context().m_windowWidth) / 2.0f + 5.0f;

	if (m_bgHorizontalPos2 >= static_cast<float>(get_context().m_windowWidth) + static_cast<float>(m_background->get_width()) / 2.0f)
		m_bgHorizontalPos2 = -static_cast<float>(get_context().m_windowWidth) / 2.0f + 5.0f;

	m_bgHorizontalPos1 += timestep * BG_SCROLL_VELOCITY;
	m_bgHorizontalPos2 += timestep * BG_SCROLL_VELOCITY;

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