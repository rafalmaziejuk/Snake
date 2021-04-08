#include "SpriteRenderer.h"
#include "Shader.h"
#include "Sprite.h"
#include "Buffer.h"
#include "VertexArray.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(void) :
	m_shader(Shader::create_shader("sprite", "assets/shaders/sprite.glsl")),
	m_vao(VertexArray::create_vertex_array())
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

	std::shared_ptr<VertexBuffer> vbo = VertexBuffer::create_vertex_buffer(vertices, sizeof(vertices));
	BufferLayout layout =
	{
		{ Type::FLOAT4 }
	};
	vbo->set_layout(layout);
	m_vao->set_vertex_buffer(vbo);

	uint32_t indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	std::shared_ptr<ElementBuffer> ebo = ElementBuffer::create_element_buffer(indices, sizeof(indices) / sizeof(uint32_t));
	m_vao->set_element_buffer(ebo);
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

	m_vao->bind();
	glDrawElements(GL_TRIANGLES, m_vao->get_element_buffer()->get_count(), GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}