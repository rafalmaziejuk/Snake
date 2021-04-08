#include "Shader.h"
#include "../Utils/FileIO.h"

#include <glad/glad.h>

#include <iostream>

Shader::Shader(const std::string &name, const std::string &vert, const std::string &frag) :
	m_name(name)
{
	std::string vertexShader = FileIO::file_read(vert);
	std::string fragmentShader = FileIO::file_read(frag);

	std::unordered_map<GLenum, std::string> shaderSources;
	shaderSources[GL_VERTEX_SHADER] = vertexShader;
	shaderSources[GL_FRAGMENT_SHADER] = fragmentShader;

	compile(shaderSources);
}

Shader::Shader(const std::string &name, const std::string &filepath) :
	m_name(name)
{
	std::string shaderSource = FileIO::file_read(filepath);
	size_t foundVert = shaderSource.find("#type vertex");
	size_t foundFrag = shaderSource.find("#type fragment");
	size_t sourceEnd = shaderSource.find_last_of("\r\n");

	assert(foundVert != std::string::npos && foundFrag != std::string::npos);

	foundVert = shaderSource.find_first_of("\r\n", foundVert) + 1; //Start of vertex shader source code
	std::string vertexShader = shaderSource.substr(foundVert, foundFrag - foundVert);

	foundFrag = shaderSource.find_first_of("\r\n", foundFrag) + 1; //Start of fragment shader source code
	std::string fragmentShader = shaderSource.substr(foundFrag, sourceEnd - foundFrag);

	std::unordered_map<GLenum, std::string> shaderSources;
	shaderSources[GL_VERTEX_SHADER] = vertexShader;
	shaderSources[GL_FRAGMENT_SHADER] = fragmentShader;

	compile(shaderSources);
}

Shader::~Shader(void)
{
	glDeleteProgram(m_id);
}

void Shader::compile(std::unordered_map<GLenum, std::string> shaderSources)
{
	GLint isCompiled;
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	m_id = glCreateProgram();

	const GLchar *vertSource = shaderSources[GL_VERTEX_SHADER].c_str();
	const GLchar *fragSource = shaderSources[GL_FRAGMENT_SHADER].c_str();
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

void Shader::bind(void) const
{
	glUseProgram(m_id);
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

std::shared_ptr<Shader> Shader::create_shader(const std::string &name, const std::string &vert, const std::string &frag)
{
	return std::make_shared<Shader>(name, vert, frag);
}

std::shared_ptr<Shader> Shader::create_shader(const std::string &name, const std::string &filepath)
{
	return std::make_shared<Shader>(name, filepath);
}