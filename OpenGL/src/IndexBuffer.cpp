#include "IndexBuffer.h"
#include <GL/glew.h>
IndexBuffer::IndexBuffer(const void* data, unsigned int count)
{
    m_count = count;
    glGenBuffers(1, &m_RenderedID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderedID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count *sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RenderedID);
}

void IndexBuffer::BindBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderedID);
}

void IndexBuffer::unBindBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
