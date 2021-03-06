#pragma once

#include "Engine/Graphics/Texture.h"

#include <glm/glm.hpp>

#include <cmath>

namespace Engine
{

	class Sprite
	{
	private:
		std::shared_ptr<Texture> m_texture;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_angle;

	public:
		Sprite(void) :
			m_texture(),
			m_position({ 0, 0 }), 
			m_size({ 0, 0 }),
			m_angle(0.0f)
		{

		}

		Sprite(const std::shared_ptr<Texture> &texture) :
			m_texture(texture),
			m_position(),
			m_size(texture->get_size()),
			m_angle(0.0f)
		{

		}

		Sprite(const std::shared_ptr<Texture> &texture, const glm::vec2 &position, const glm::vec2 &size, float angle = 0.0f) :
			m_texture(texture),
			m_position(position),
			m_size(size),
			m_angle(angle)
		{

		}

		Sprite(const Sprite &sprite) :
			m_texture(sprite.m_texture),
			m_position(sprite.m_position),
			m_size(sprite.m_size),
			m_angle(sprite.m_angle)
		{

		}

		inline void bind_texture(uint32_t unit) const { m_texture->bind(unit); }

		inline glm::vec2 get_position(void) const { return m_position; }
		inline void set_position(const glm::vec2 &position) { m_position = position; }

		inline glm::vec2 get_default_size(void) const { return m_texture->get_size(); }
		inline glm::vec2 get_size(void) const { return m_size; }
		inline void set_size(const glm::vec2 &size) { m_size = size; }

		inline void set_scale(float scaleFactor) { m_size = get_default_size() * scaleFactor; }

		inline float get_angle(void) const { return m_angle; }
		void set_angle(float angle)
		{
			m_angle = static_cast<float>(fmod(angle, 360));

			if (m_angle < 0)
				m_angle += 360.0f;
		}
		inline void rotate(float angle)
		{
			set_angle(m_angle + angle);
		}
	};

}