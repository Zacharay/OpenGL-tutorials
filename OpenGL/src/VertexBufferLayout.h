#pragma once
#include <GL/glew.h>
#include <vector>
struct VertexLayoutElement {
	unsigned int type;
	unsigned int count;
	unsigned int normalized;
	static unsigned int GetTypeSize(unsigned int type)
	{
		switch (type) {
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexLayoutElement>m_elements;
	unsigned int m_stride;
public:
	VertexBufferLayout() :m_stride(0) {};

	void Push(unsigned int count,unsigned int type);
	inline const std::vector<VertexLayoutElement>& GetElements()const { return m_elements; };
	inline unsigned int GetStride() const { return m_stride; };
};