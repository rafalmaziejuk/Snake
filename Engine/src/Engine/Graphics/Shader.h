#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <unordered_map>

namespace Engine
{

	class Shader
	{
	private:
		uint32_t m_id;
		std::string m_name;

	private:
		void compile(std::unordered_map<GLenum, std::string> shaderSources);

	public:
		Shader(const std::string &name, const std::string &vert, const std::string &frag);
		Shader(const std::string &name, const std::string &filepath);
		~Shader(void);

		void bind(void) const;

		void set_int(const std::string &name, int value);
		void set_float(const std::string &name, float value);
		void set_vec3f(const std::string &name, const glm::vec3 &vec);
		void set_mat4(const std::string &name, const glm::mat4 &mat);
	};

}