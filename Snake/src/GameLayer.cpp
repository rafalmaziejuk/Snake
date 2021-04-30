#include "GameLayer.h"
#include "StateIdentifiers.h"
#include "MenuState.h"
#include "GameState.h"
#include "GameoverState.h"

#include <Engine/Core/Core.h>
#include <Engine/Core/Application.h>
#include <Engine/Events/KeyboardEvent.h>
#include <Engine/Events/MouseEvent.h>

#include <imgui.h>

GameLayer::GameLayer(void) :
	m_stateManager
	({ 
		Engine::Application::get().get_window().get_width(),
		Engine::Application::get().get_window().get_height() 
	})
{

}

void GameLayer::on_attach(void)
{
	register_states();
	m_stateManager.push_state(ID::MENU_STATE);
}

void GameLayer::on_detach(void)
{

}

void GameLayer::on_event(Engine::Event &e)
{
	
}

void GameLayer::on_update(float timestep)
{
	m_stateManager.handle_input();
	m_stateManager.update(timestep);

	if (m_stateManager.is_empty())
		Engine::Application::get().close();
}

void GameLayer::on_render(void)
{
	m_stateManager.render();
}

void GameLayer::on_imgui_render(void)
{
	ImGui::Begin("FPS");
	ImGui::Text("%.3f ms / %.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void GameLayer::register_states(void)
{
	m_stateManager.register_state<MenuState>(ID::MENU_STATE);
	m_stateManager.register_state<GameState>(ID::GAME_STATE);
	m_stateManager.register_state<GameoverState>(ID::GAMEOVER_STATE);
}