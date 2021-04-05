#include "Shader.h"
#include "../Utils/FileIO.h"

#include <glad/glad.h>

#include <iostream>
#include <vector>

Shader::Shader(const std::string &vert, const std::string &frag)
{
	std::string vertexShader = FileIO::file_read(vert);
	std::string fragmentShader = FileIO::file_read(frag);
	const GLchar *vertexShaderSource = vertexShader.c_str();
	const GLchar *fragmentShaderSource = fragmentShader.c_str();

	compile(vertexShaderSource, fragmentShaderSource);
}

Shader::~Shader(void)
{
	glDeleteProgram(m_id);
}

void Shader::compile(const char *vertSource, const char *fragSource)
{
	GLint isCompiled;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	m_id = glCreateProgram();

	glShaderSource(vertexShader, 1, &vertSource, nullptr);
	glShaderSource(fragmentShader, 1, &fragSource, nullptr);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
		std::vector<GLchar> infoLog(length);
		glGetShaderInfoLog(vertexShader, length, &length, &infoLog[0]);

		glDeleteShader(vertexShader);
		std::cout << infoLog.data() << std::endl;
	}

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
		std::vector<GLchar> infoLog(length);
		glGetShaderInfoLog(fragmentShader, length, &length, &infoLog[0]);

		glDeleteShader(fragmentShader);
		std::cout << infoLog.data() << std::endl;
	}

	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);
	glGetProgramiv(m_id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
		std::vector<GLchar> infoLog(length);
		glGetProgramInfoLog(m_id, length, &length, &infoLog[0]);

		glDeleteProgram(m_id);
		std::cout << infoLog.data() << std::endl;
	}

	glDetachShader(m_id, vertexShader);
	glDetachShader(m_id, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use(void) const
{
	glUseProgram(m_id);
}

unsigned int Shader::get_id(void) const
{
	return m_id;
}

void Shader::set_int(const std::string &name, int value)
{
	GLint location = glGetUniformLocation(m_id, name.c_str());
	glUniform1i(location, value);
}

void Shader::set_float(const std::string &name, float value)
{
	GLint location = glGetUniformLocation(m_id, name.c_str());
	glUniform1f(location, value);
}

void Shader::set_vec3f(const std::string &name, const glm::vec3 &vec)
{
	GLint location = glGetUniformLocation(m_id, name.c_str());
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::set_mat4(const std::string & name, const glm::mat4 &mat)
{
	GLint location = glGetUniformLocation(m_id, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}