#pragma once

#include <glm/glm.hpp>

#include <string>

class Shader
{
private:
	uint32_t m_id;

private:
	void compile(const char *vertSource, const char *fragSource);

public:
	Shader(const std::string &vert, const std::string &frag);
	~Shader(void);

	void use(void) const;
	unsigned int get_id(void) const;

	void set_int(const std::string &name, int value);
	void set_float(const std::string &name, float value);
	void set_mat4(const std::string &name, const glm::mat4 &mat);
};