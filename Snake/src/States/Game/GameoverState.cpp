#include "GameoverState.h"
#include "../../Utils/InputManager.h"
#include "../../Utils/ImGui/ImGuiRenderer.h"
#include "../../Graphics/Renderer.h"

#include <GLFW/glfw3.h>

#include <sstream>

const float GameoverState::BG_SCROLL_VELOCITY = 15.0f;
extern uint16_t playerScore;

GameoverState::GameoverState(StateManager &stateManager, Context context) :
	State(stateManager, context),
	m_inputManager(InputManager::get_instance()),
	m_textRenderer(get_context().m_windowWidth, get_context().m_windowHeight),
	m_replayButton(Texture::create("assets/textures/replay_button.png")),
	m_exitButton(Texture::create("assets/textures/exit_button.png")),
	m_overlay(Texture::create("assets/textures/gameover.png")),
	m_background(Texture::create("assets/textures/menu_bg.png")),
	m_bgHorizontalPos1(static_cast<float>(m_background->get_width()) / 2.0f),
	m_bgHorizontalPos2(-static_cast<float>(m_background->get_width()) / 2.0f + 10.0f)
{
	m_textRenderer.load("assets/fonts/EdgeOfTheGalaxyRegular.otf", 70);

	m_replayButton.set_scale(0.80f);
	m_replayButton.set_position
	(
		{
			static_cast<float>(get_context().m_windowWidth / 2.0f),
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

GameoverState::~GameoverState(void)
{

}

void GameoverState::draw(void) const
{
	Renderer::draw({ m_bgHorizontalPos1, get_context().m_windowHeight / 2 }, m_background);
	Renderer::draw({ m_bgHorizontalPos2, get_context().m_windowHeight / 2 }, m_background);
	Renderer::draw({ get_context().m_windowWidth / 2, get_context().m_windowHeight / 2 }, m_overlay);
	Renderer::draw(m_replayButton);
	Renderer::draw(m_exitButton);

	std::stringstream ss;
	if (playerScore < 10)
		ss << "00" << playerScore;
	else if (playerScore >= 10 && playerScore < 100)
		ss << "0" << playerScore;
	else
		ss << playerScore;

	m_textRenderer.render_text(ss.str(), { 345.0f, 145.0f }, 1.0f);
}

void GameoverState::imgui_render(void) const
{
	
}

bool GameoverState::update(float timestep)
{
	if (m_bgHorizontalPos1 >= static_cast<float>(get_context().m_windowWidth) + static_cast<float>(m_background->get_width()) / 2.0f)
		m_bgHorizontalPos1 = -static_cast<float>(get_context().m_windowWidth) / 2.0f + 10.0f;

	if (m_bgHorizontalPos2 >= static_cast<float>(get_context().m_windowWidth) + static_cast<float>(m_background->get_width()) / 2.0f)
		m_bgHorizontalPos2 = -static_cast<float>(get_context().m_windowWidth) / 2.0f + 10.0f;

	m_bgHorizontalPos1 += timestep * BG_SCROLL_VELOCITY;
	m_bgHorizontalPos2 += timestep * BG_SCROLL_VELOCITY;

	return true;
}

bool GameoverState::handle_input(void)
{
	auto mousePosition = m_inputManager.get_mouse_position();

	//Play button
	if (mousePosition.x >= 355.0f && mousePosition.x <= 445.0f &&
		mousePosition.y >= 250.0f && mousePosition.y <= 345.0f)
	{
		m_replayButton.set_scale(0.85f);
		if (m_inputManager.is_key_pressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			pop_state();
			push_state(ID::GAME_STATE);
		}
	}
	else
		m_replayButton.set_scale(0.80f);

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