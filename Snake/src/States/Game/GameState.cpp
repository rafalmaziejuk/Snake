#include "GameState.h"
#include "../../Utils/ImGui/ImGuiRenderer.h"

GameState::GameState(StateManager &stateManager, Context context) :
	State(stateManager, context),
	m_world(context.m_windowWidth, context.m_windowHeight)
{

}

GameState::~GameState(void)
{

}

void GameState::draw(void) const
{
	ImGuiRenderer::begin();
	ImGui::Begin("FPS");
	ImGui::Text("%.3f ms / %.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
	ImGuiRenderer::end(get_context().m_windowHeight, get_context().m_windowHeight);

	m_world.draw();
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