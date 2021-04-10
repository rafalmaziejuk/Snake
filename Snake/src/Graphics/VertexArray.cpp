#include "VertexArray.h"

#include <glad/glad.h>

static GLenum get_opengl_data_type(Type type)
{
	switch (type)
	{
		case Type::FLOAT:  return GL_FLOAT;
		case Type::FLOAT2: return GL_FLOAT;
		case Type::FLOAT3: return GL_FLOAT;
		case Type::FLOAT4: return GL_FLOAT;
	}

	return 0;
}

VertexArray::VertexArray(void)
{
	glGenVertexArrays(1, &m_id);
}

void VertexArray::bind(void) const
{
	glBindVertexArray(m_id);
}

void VertexArray::set_vertex_buffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
{
	bind();
	vertexBuffer->bind();

	//Iterate through layout vertex buffer elements
	const auto &layout = vertexBuffer->get_layout();
	for (uint8_t i = 0; i < layout.get_vbelement_count(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer
		(
			i,
			layout[i].get_component_count(),
			get_opengl_data_type(layout[i].m_type),
			layout[i].m_normalized ? GL_TRUE : GL_FALSE,
			layout.get_stride(),
			(const void *)layout[i].m_offset
		);
	}

	m_vertexBuffer = vertexBuffer;
}

void VertexArray::set_element_buffer(const std::shared_ptr<ElementBuffer> &elementBuffer)
{
	bind();
	elementBuffer->bind();
	m_elementBuffer = elementBuffer;
}