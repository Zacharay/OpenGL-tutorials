#include "VertexArray.h"
#include "vector"
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RenderedID);
	glBindVertexArray(m_RenderedID);

}

VertexArray::~VertexArray()
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	vbo.BindBuffer();
	auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i=0;i<elements.size();i++)
	{
		auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexLayoutElement::GetTypeSize(element.type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RenderedID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
