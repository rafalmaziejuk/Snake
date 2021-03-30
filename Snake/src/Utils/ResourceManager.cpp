#include "ResourceManager.h"

ResourceManager * ResourceManager::m_instance = nullptr;

ResourceManager & ResourceManager::get_instance(void)
{
	if (m_instance == nullptr)
		m_instance = new ResourceManager();

	return *m_instance;
}

void ResourceManager::load_shader(const std::string &name, const std::string &vert, const std::string &frag)
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(vert, frag);
	m_shaders.insert(std::make_pair(name, std::move(shader)));
}

void ResourceManager::load_texture(const std::string &name, const std::string &filepath)
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(filepath);
	m_textures.insert(std::make_pair(name, std::move(texture)));
}

std::shared_ptr<Shader> ResourceManager::get_shader(const std::string &name)
{
	return m_shaders[name];
}

std::shared_ptr<Texture> ResourceManager::get_texture(const std::string &name)
{
	return m_textures[name];
}