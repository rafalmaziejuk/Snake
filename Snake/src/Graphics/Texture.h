#pragma once

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

	static std::shared_ptr<Texture> create_texture(const std::string &filepath);
};