#pragma once

#include "Shader.h"

#include <memory>

class Sprite;

class SpriteRenderer
{
private:
	SpriteRenderer(const SpriteRenderer &manager) = delete;
	SpriteRenderer & operator=(const SpriteRenderer &manager) = delete;

public:
	inline static SpriteRenderer & get_instance(void)
	{
		static SpriteRenderer instance;
		return instance;
	}

private:
	std::shared_ptr<Shader> m_shader;
	uint32_t m_vao;

public:
	SpriteRenderer(void);
	~SpriteRenderer(void);

	void draw(const Sprite &sprite) const;
};