#pragma once
class IndexBuffer {
private:
	unsigned int m_RenderedID;
	unsigned int m_count;
public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void BindBuffer()const;
	void unBindBuffer()const;
	inline unsigned int getCount() const{ return m_count; };
};