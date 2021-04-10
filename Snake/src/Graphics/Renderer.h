#pragma once

#include <glm/vec4.hpp>

#include <cstdint>

class Sprite;

class Renderer
{
public:
	static void init(uint16_t width, uint16_t height);
	static void shutdown(void);

	static void set_viewport(uint16_t width, uint16_t height);
	static void set_clear_color(const glm::vec4 &color);

	static void clear(void);

	static void draw(const Sprite &sprite);
};