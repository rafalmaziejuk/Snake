#pragma once

#include <Engine/Core/Layer.h>
#include <Engine/Events/KeyboardEvent.h>
#include <Engine/Events/MouseEvent.h>

#include <imgui.h>

#include <iostream>

namespace Engine
{

	class GameLayer : public Layer
	{
	private:
		std::shared_ptr<Texture> m_texture;
		Sprite m_sprite;

	private:
		bool on_key_pressed(KeyPressedEvent &e)
		{
			switch (e.get_key_code())
			{
				case Key::A:
					std::cout << "A\n";
					break;

				case Key::D:
					std::cout << "D\n";
					break;

				case Key::W:
					std::cout << "W\n";
					break;

				case Key::S:
					std::cout << "S\n";
					break;
			}

			return true;
		}

		bool on_mouse_button_pressed(MouseButtonPressedEvent &e)
		{
			if (e.get_mouse_button() == Mouse::ButtonLeft)
				std::cout << "Left\n";

			if (e.get_mouse_button() == Mouse::ButtonRight)
				std::cout << "Right\n";

			return true;
		}

	public:
		virtual ~GameLayer(void) = default;

		virtual void on_attach(void) override
		{
			m_texture = Texture::create("assets/textures/exit_button.png");
			m_sprite = Sprite(m_texture, { 450, 300 }, m_texture->get_size());
		}

		virtual void on_detach(void) override
		{

		}

		virtual void on_event(Event &e) 
		{ 
			EventDispatcher dispatcher(e);
			dispatcher.dispatch<MouseButtonPressedEvent>(EN_BIND_EVENT(GameLayer::on_mouse_button_pressed));
			dispatcher.dispatch<KeyPressedEvent>(EN_BIND_EVENT(GameLayer::on_key_pressed));
		}

		virtual void on_update(float timestep) 
		{
			float time = (float)glfwGetTime();
			m_sprite.rotate(sin(time));
		}

		virtual void on_render(void) 
		{
			Renderer::draw
			(
				{ Application::get().get_window().get_width() / 2, Application::get().get_window().get_height() / 2 },
				m_texture
			);

			Renderer::draw(m_sprite);
		}

		virtual void on_imgui_render(void) 
		{  
			ImGui::ShowDemoWindow();
		}
	};

}