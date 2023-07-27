#pragma once


class VertexBuffer {
private:
	unsigned int m_RenderedID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void BindBuffer()const;
	void unBindBuffer()const;
};