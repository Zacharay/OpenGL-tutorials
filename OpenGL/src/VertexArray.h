#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
	unsigned int m_RenderedID;
public:
	VertexArray();
	~VertexArray();
	void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
};