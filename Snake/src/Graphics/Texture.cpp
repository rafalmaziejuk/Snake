#include "Texture.h"

#include <stb_image.h>
#include <glad/glad.h>

#include <cassert>

std::shared_ptr<Texture> Texture::create_texture(const std::string &filepath)
{
	return std::make_shared<Texture>(filepath);
}

Texture::Texture(const std::string &filepath)
{
	int width, height, channels;
	stbi_uc *data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
	assert(data);

	m_width = width;
	m_height = height;

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLenum internalFormat = 0;
	GLenum dataFormat = 0;

	if (channels == 3)
	{
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}
	else if (channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

Texture::~Texture(void)
{
	glDeleteTextures(1, &m_id);
}

void Texture::bind(uint32_t slot) const
{
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, m_id);
}