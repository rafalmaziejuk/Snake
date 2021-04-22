#pragma once

#include "Engine/Graphics/Texture.h"
#include "Engine/Graphics/Sprite.h"

#include <glm/glm.hpp>

namespace Engine
{

	class Renderer
	{
	public:
		static void init(uint16_t width, uint16_t height);
		static void shutdown(void);

		static void set_viewport(uint16_t width, uint16_t height);
		static void set_clear_color(const glm::vec4 &color);

		static void clear(void);

		static void draw(const Sprite &sprite);
		static void draw(const glm::vec2 &position, const std::shared_ptr<Texture> &texture);
	};

}