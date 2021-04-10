#pragma once

#include <vector>
#include <cstdint>
#include <memory>
#include <initializer_list>

enum class Type : uint8_t
{
	NONE = 0,
	FLOAT,
	FLOAT2,
	FLOAT3,
	FLOAT4
};

static uint8_t get_type_size(Type type)
{
	switch (type)
	{
		case Type::FLOAT:  return 1 * sizeof(float);
		case Type::FLOAT2: return 2 * sizeof(float);
		case Type::FLOAT3: return 3 * sizeof(float);
		case Type::FLOAT4: return 4 * sizeof(float);
	}

	return 0;
}

class BufferLayout
{
private:
	struct VBElement
	{
		uint32_t m_size;
		Type m_type;
		bool m_normalized;
		uint16_t m_offset;

		VBElement(Type type, bool normalized = false) :
			m_size(get_type_size(type)),
			m_type(type),
			m_normalized(normalized),
			m_offset(0)
		{

		}

		uint8_t get_component_count(void) const
		{
			switch (m_type)
			{
				case Type::FLOAT:  return 1;
				case Type::FLOAT2: return 2;
				case Type::FLOAT3: return 3;
				case Type::FLOAT4: return 4;
			}

			return 0;
		}
	};

private:
	std::vector<VBElement> m_vbElements;
	uint32_t m_stride;

private:
	void calculate_stride(void)
	{
		uint16_t offset = 0;
		for (auto &element : m_vbElements)
		{
			element.m_offset = offset;
			m_stride += element.m_size;
			offset += element.m_size;
		}
	}

public:
	BufferLayout(void) = default;
	BufferLayout(std::initializer_list<VBElement> elements) :
		m_vbElements(elements),
		m_stride(0)
	{
		calculate_stride();
	}

	inline size_t get_vbelement_count(void) const { return m_vbElements.size(); }
	inline uint32_t get_stride(void) const { return m_stride; }

	inline const VBElement & operator[](uint8_t index) const
	{
		return m_vbElements[index];
	}
};

class VertexBuffer
{
private:
	uint32_t m_id;
	BufferLayout m_layout;

public:
	VertexBuffer(const float *data, uint32_t size);
	~VertexBuffer(void);

	inline void set_layout(const BufferLayout &layout) { m_layout = layout; }
	inline const BufferLayout & get_layout(void) const { return m_layout; }
	void bind(void) const;
};

class ElementBuffer
{
private:
	uint32_t m_id;
	uint8_t m_elementCount;

public:
	ElementBuffer(const uint32_t *data, uint8_t elementCount);
	~ElementBuffer(void);

	inline uint8_t get_count(void) const { return m_elementCount; }
	void bind(void) const;
};