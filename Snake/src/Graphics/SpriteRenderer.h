#pragma once

#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>

#include <memory>

class SpriteRenderer
{
private:
	std::shared_ptr<Shader> m_shader;
	uint32_t m_vao;

public:
	SpriteRenderer(const std::shared_ptr<Shader> &shader);
	~SpriteRenderer(void);

	void draw(const std::shared_ptr<Texture> &texture, const glm::vec2 &position, const glm::vec2 &size);
};