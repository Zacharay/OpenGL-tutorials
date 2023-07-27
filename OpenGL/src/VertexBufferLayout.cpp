#include "VertexBufferLayout.h"
#include <iostream>

void VertexBufferLayout::Push(unsigned int count,unsigned int type)
{
	m_elements.push_back({ type,count,GL_FALSE });
	m_stride += count*VertexLayoutElement::GetTypeSize(type);
}

