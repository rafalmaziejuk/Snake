#pragma once

#include <string>
#include <memory>

class Texture
{
public:
	virtual void bind(uint32_t unit) const = 0;

	static std::shared_ptr<Texture> create_texture(const std::string &filepath);
};

class OpenGLTexture : public Texture
{
private:
	uint32_t m_id;
	uint16_t m_width;
	uint16_t m_height;

public:
	OpenGLTexture(const std::string &filepath);
	~OpenGLTexture(void);

	virtual void bind(uint32_t unit) const override;
};