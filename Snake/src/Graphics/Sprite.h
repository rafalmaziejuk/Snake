#pragma once

#include "Texture.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>

class Sprite
{
private:
	std::shared_ptr<Texture> m_texture;
	glm::vec2 m_position;
	glm::vec2 m_size;

public:
	Sprite(const std::shared_ptr<Texture> &texture, const glm::vec2 &position, const glm::vec2 &size) :
		m_texture(texture),
		m_position(position),
		m_size(size)
	{

	}
	
	inline glm::vec2 get_position(void) const { return m_position; }
	inline glm::vec2 get_size(void) const { return m_size; }
	inline void bind_texture(uint32_t unit) const { m_texture->bind(unit); }
};