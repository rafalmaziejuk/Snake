#include "SpriteRenderer.h"
#include "Sprite.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(void) :
	m_shader(nullptr),
	m_vao(0)
{
	float vertices[] =
	{
		//position		//tex coords
		0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 0.0f,		1.0f, 0.0f,
		0.0f, 0.0f,		0.0f, 0.0f,
		0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, 0.0f,		1.0f, 0.0f
	};
	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	uint32_t vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
	m_shader->use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(sprite.get_position(), 0.0f));
	model = glm::scale(model, glm::vec3(sprite.get_size(), 1.0f));
	m_shader->set_mat4("model", model);

	sprite.bind_texture(GL_TEXTURE0);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}