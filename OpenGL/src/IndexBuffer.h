#pragma once
class IndexBuffer {
private:
	unsigned int m_RenderedID;
	unsigned int m_count;
public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void BindBuffer();
	void unBindBuffer();
	inline unsigned int getCount() { return m_count; };
};