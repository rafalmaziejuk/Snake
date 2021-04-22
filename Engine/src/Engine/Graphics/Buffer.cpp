#include "Engine/Graphics/Buffer.h"

#include <glad/glad.h>

namespace Engine
{

	VertexBuffer::VertexBuffer(const float *data, uint32_t size)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer(void)
	{
		glDeleteBuffers(1, &m_id);
	}

	void VertexBuffer::bind(void) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::create(const float *data, uint32_t size)
	{
		return std::make_shared<VertexBuffer>(data, size);
	}

	ElementBuffer::ElementBuffer(const uint32_t *data, uint32_t elementCount) :
		m_elementCount(elementCount)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * m_elementCount, data, GL_STATIC_DRAW);
	}

	ElementBuffer::~ElementBuffer(void)
	{
		glDeleteBuffers(1, &m_id);
	}

	void ElementBuffer::bind(void) const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	std::shared_ptr<ElementBuffer> ElementBuffer::create(const uint32_t *data, uint32_t elementCount)
	{
		return std::make_shared<ElementBuffer>(data, elementCount);
	}

}