#pragma once

#include <glm/glm.hpp>

#include <string>
#include <memory>

namespace Engine
{

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

		static std::shared_ptr<Texture> create(const std::string &filepath);
	};

}