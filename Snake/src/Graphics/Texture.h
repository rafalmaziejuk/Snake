#pragma once

#include <glm/vec2.hpp>

#include <string>
#include <memory>

class Texture
{
private:
	uint32_t m_id;
	uint16_t m_width;
	uint16_t m_height;

public:
	Texture(const std::string &filepath);
	~Texture(void);

	void bind(uint32_t unit) const;

	inline uint16_t get_width(void) const { return m_width; }
	inline uint16_t get_height(void) const { return m_height; }
	inline glm::vec2 get_size(void) const { return { m_width, m_height }; }

	static std::shared_ptr<Texture> create_texture(const std::string &filepath);
};