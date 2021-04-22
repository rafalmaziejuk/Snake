#pragma once

#include "Engine/Graphics/Shader.h"

#include <glm/glm.hpp>

#include <memory>
#include <unordered_map>

namespace Engine
{

	//Temporary solution
	class TextRenderer
	{
	private:
		struct Character
		{
			uint32_t m_textureID;
			uint32_t m_offset;
			glm::ivec2 m_size;
			glm::ivec2 m_bearing;
		};

	private:
		uint32_t m_vao;
		uint32_t m_vbo;
		std::unordered_map<char, Character> m_characters;
		std::shared_ptr<Shader> m_shader;

	public:
		TextRenderer(uint16_t windowWidth, uint16_t windowHeight);

		void load(const std::string &filepath, uint8_t fontSize);
		void render_text(const std::string &text, glm::fvec2 position, float scale, const glm::vec3 &color = glm::vec3(1.0f)) const;
	};

}