#include "SpriteRenderer.h"
#include "Shader.h"
#include "Sprite.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(void) :
	m_shader(Shader::create_shader("sprite", "assets/shaders/sprite.glsl")),
	m_vao(0)
{
	//temp
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	m_shader->bind();
	m_shader->set_int("sprite", 0);
	m_shader->set_mat4("projection", projection);

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, //bottom-left
		 0.5f, -0.5f, 1.0f, 0.0f, //bottom-right
		 0.5f,  0.5f, 1.0f, 1.0f, //top-right
		-0.5f,  0.5f, 0.0f, 1.0f  //top-left
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

SpriteRenderer::~SpriteRenderer(void)
{
	glDeleteVertexArrays(1, &m_vao);
}

void SpriteRenderer::draw(const Sprite &sprite) const
{
	m_shader->bind();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(sprite.get_position(), 0.0f));
	model = glm::rotate(model, glm::radians(sprite.get_angle()), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(sprite.get_size(), 1.0f));
	m_shader->set_mat4("model", model);

	sprite.bind_texture(GL_TEXTURE0);

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}