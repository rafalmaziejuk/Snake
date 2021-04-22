#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/VertexArray.h"
#include "Engine/Graphics/Sprite.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace Engine
{

	struct Data
	{
		glm::mat4 m_projectionMatrix;
		std::unique_ptr<Shader> m_spriteShader;
		std::unique_ptr<VertexArray> m_spriteVertexArray;
	};

	static Data rendererData;

	void Renderer::init(uint16_t width, uint16_t height)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		rendererData.m_projectionMatrix = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
		rendererData.m_spriteShader = std::make_unique<Shader>("sprite", "assets/shaders/sprite.glsl");
		rendererData.m_spriteVertexArray = std::make_unique<VertexArray>();

		rendererData.m_spriteShader->bind();
		rendererData.m_spriteShader->set_int("sprite", 0);
		rendererData.m_spriteShader->set_mat4("projection", rendererData.m_projectionMatrix);

		//Quad with origin in its center
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, //bottom-left
			 0.5f, -0.5f, 1.0f, 0.0f, //bottom-right
			 0.5f,  0.5f, 1.0f, 1.0f, //top-right
			-0.5f,  0.5f, 0.0f, 1.0f  //top-left
		};

		auto vbo = VertexBuffer::create(vertices, sizeof(vertices));
		BufferLayout layout =
		{
			{ Type::FLOAT4 }
		};
		vbo->set_layout(layout);
		rendererData.m_spriteVertexArray->set_vertex_buffer(vbo);

		uint32_t indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		auto ebo = ElementBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));
		rendererData.m_spriteVertexArray->set_element_buffer(ebo);
	}

	void Renderer::shutdown(void)
	{

	}

	void Renderer::set_viewport(uint16_t width, uint16_t height)
	{
		glViewport(0, 0, width, height);
	}

	void Renderer::set_clear_color(const glm::vec4 &color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::clear(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::draw(const Sprite &sprite)
	{
		glm::mat4 model =
			glm::translate(glm::mat4(1.0f), glm::vec3(sprite.get_position(), 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(sprite.get_angle()), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(sprite.get_size(), 1.0f));

		rendererData.m_spriteShader->bind();
		rendererData.m_spriteShader->set_mat4("model", model);

		sprite.bind_texture(GL_TEXTURE0);

		rendererData.m_spriteVertexArray->bind();
		glDrawElements(GL_TRIANGLES, rendererData.m_spriteVertexArray->get_element_buffer()->get_count(), GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Renderer::draw(const glm::vec2 &position, const std::shared_ptr<Texture> &texture)
	{
		glm::mat4 model =
			glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(texture->get_size(), 1.0f));

		rendererData.m_spriteShader->bind();
		rendererData.m_spriteShader->set_mat4("model", model);

		texture->bind(GL_TEXTURE0);

		rendererData.m_spriteVertexArray->bind();
		glDrawElements(GL_TRIANGLES, rendererData.m_spriteVertexArray->get_element_buffer()->get_count(), GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}