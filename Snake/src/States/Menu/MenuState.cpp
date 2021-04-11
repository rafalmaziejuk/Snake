#include "MenuState.h"
#include "../../Utils/InputManager.h"
#include "../../Graphics/Texture.h"
#include "../../Graphics/Renderer.h"

#include <GLFW/glfw3.h>

const float MenuState::BG_SCROLL_VELOCITY = 20.0f;

MenuState::MenuState(StateManager &stateManager, Context context) :
	State(stateManager, context),
	m_inputManager(InputManager::get_instance()),
	m_playButton(Texture::create_texture("assets/textures/play_button.png")),
	m_exitButton(Texture::create_texture("assets/textures/exit_button.png")),
	m_menu(Texture::create_texture("assets/textures/menu.png")),
	m_background(Texture::create_texture("assets/textures/menu_bg.png")),
	m_bgHorizontalPos1(static_cast<float>(m_background->get_width()) / 2.0f),
	m_bgHorizontalPos2(-static_cast<float>(m_background->get_width()) / 2.0f)
{
	m_playButton.set_scale(0.80f);
	m_playButton.set_position
	(
		{ 
			static_cast<float>(get_context().m_windowWidth / 2.0f) + 5.0f,
			static_cast<float>(get_context().m_windowHeight / 2.0f)
		}
	);

	m_exitButton.set_scale(0.80f);
	m_exitButton.set_position
	(
		{
			static_cast<float>(get_context().m_windowWidth / 2.0f),
			static_cast<float>(get_context().m_windowHeight / 2.0f) + 150.0f
		}
	);
}

MenuState::~MenuState(void)
{

}

void MenuState::draw(void) const
{
	Renderer::draw({ m_bgHorizontalPos1, get_context().m_windowHeight / 2 }, m_background);
	Renderer::draw({ m_bgHorizontalPos2, get_context().m_windowHeight / 2 }, m_background);
	Renderer::draw({ get_context().m_windowWidth / 2, get_context().m_windowHeight / 2 }, m_menu);
	Renderer::draw(m_playButton);
	Renderer::draw(m_exitButton);
}

void MenuState::imgui_render(void) const
{

}

bool MenuState::update(float timestep)
{
	if (m_bgHorizontalPos1 >= static_cast<float>(get_context().m_windowWidth) + static_cast<float>(m_background->get_width()) / 2.0f)
		m_bgHorizontalPos1 = -static_cast<float>(get_context().m_windowWidth) / 2.0f + 10.0f;

	if (m_bgHorizontalPos2 >= static_cast<float>(get_context().m_windowWidth) + static_cast<float>(m_background->get_width()) / 2.0f)
		m_bgHorizontalPos2 = -static_cast<float>(get_context().m_windowWidth) / 2.0f + 10.0f;

	m_bgHorizontalPos1 += timestep * BG_SCROLL_VELOCITY;
	m_bgHorizontalPos2 += timestep * BG_SCROLL_VELOCITY;

	return true;
}

bool MenuState::handle_input(void)
{
	auto mousePosition = m_inputManager.get_mouse_position();
	
	//Play button
	if (mousePosition.x >= 355.0f && mousePosition.x <= 445.0f &&
		mousePosition.y >= 250.0f && mousePosition.y <= 345.0f)
	{
		m_playButton.set_scale(0.85f);
		if (m_inputManager.is_key_pressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			pop_state();
			push_state(ID::GAME_STATE);
		}
	}
	else
		m_playButton.set_scale(0.80f);

	//Exit button
	if (mousePosition.x >= 350.0f && mousePosition.x <= 445.0f &&
		mousePosition.y >= 395.0f && mousePosition.y <= 495.0f)
	{
		m_exitButton.set_scale(0.85f);
		if (m_inputManager.is_key_pressed(GLFW_MOUSE_BUTTON_LEFT))
			pop_state();
	}
	else
		m_exitButton.set_scale(0.80f);

	return true;
}