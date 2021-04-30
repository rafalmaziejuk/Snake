#pragma once

#include "StateManager.h"

#include <Engine/Core/Layer.h>

namespace Engine
{
	class KeyPressedEvent;
	class MouseButtonPressedEvent;
}

class GameLayer : public Engine::Layer
{
private:
	StateManager m_stateManager;
	void register_states(void);

public:
	GameLayer(void);
	virtual ~GameLayer(void) = default;

	virtual void on_attach(void) override;
	virtual void on_detach(void) override;

	virtual void on_event(Engine::Event &e) override;
	virtual void on_update(float timestep) override;

	virtual void on_render(void) override;
	virtual void on_imgui_render(void) override;
};