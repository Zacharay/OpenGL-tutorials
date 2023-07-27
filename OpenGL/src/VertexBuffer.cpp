#include "VertexBuffer.h"
#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{

    glGenBuffers(1, &m_RenderedID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RenderedID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RenderedID);
}

void VertexBuffer::BindBuffer() const
{
   glBindBuffer(GL_ARRAY_BUFFER, m_RenderedID);
}

void VertexBuffer::unBindBuffer()const
{
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}
