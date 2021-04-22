#pragma once

#include "Engine/Graphics/Buffer.h"

namespace Engine
{

	class VertexArray
	{
	private:
		uint32_t m_id;
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<ElementBuffer> m_elementBuffer;

	public:
		VertexArray(void);

		void bind(void) const;

		void set_vertex_buffer(const std::shared_ptr<VertexBuffer> &vertexBuffer);
		inline const std::shared_ptr<VertexBuffer> & get_vertex_buffer(void) const { return m_vertexBuffer; }

		void set_element_buffer(const std::shared_ptr<ElementBuffer> &elementBuffer);
		inline const std::shared_ptr<ElementBuffer> & get_element_buffer(void) const { return m_elementBuffer; }
	};

}