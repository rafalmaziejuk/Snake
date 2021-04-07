#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <memory>
#include <unordered_map>

class Shader
{
public:
	virtual void bind(void) const = 0;

	virtual void set_int(const std::string &name, int value) = 0;
	virtual void set_float(const std::string &name, float value) = 0;
	virtual void set_vec3f(const std::string &name, const glm::vec3 &vec) = 0;
	virtual void set_mat4(const std::string &name, const glm::mat4 &mat) = 0;

	static std::shared_ptr<Shader> create_shader(const std::string &name, const std::string &vert, const std::string &frag);
	static std::shared_ptr<Shader> create_shader(const std::string &name, const std::string &filepath);
};

class OpenGLShader : public Shader
{
private:
	uint32_t m_id;
	std::string m_name;

private:
	void compile(std::unordered_map<GLenum, std::string> shaderSources);

public:
	OpenGLShader(const std::string &name, const std::string &vert, const std::string &frag);
	OpenGLShader(const std::string &name, const std::string &filepath);
	~OpenGLShader(void);

	virtual void bind(void) const override;

	virtual void set_int(const std::string &name, int value) override;
	virtual void set_float(const std::string &name, float value) override;
	virtual void set_vec3f(const std::string &name, const glm::vec3 &vec) override;
	virtual void set_mat4(const std::string &name, const glm::mat4 &mat) override;
};