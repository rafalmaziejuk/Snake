#pragma once

#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"

#include <map>
#include <memory>

class ResourceManager
{
private:
	std::map<std::string, std::shared_ptr<Shader>> m_shaders;
	std::map<std::string, std::shared_ptr<Texture>> m_textures;

public:
	void load_shader(const std::string &name, const std::string &vert, const std::string &frag);
	void load_texture(const std::string &name, const std::string &filepath);

	std::shared_ptr<Shader> get_shader(const std::string &name);
	std::shared_ptr<Texture> get_texture(const std::string &name);
};