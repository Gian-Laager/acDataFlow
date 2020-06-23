#include "VertexBuffer.h"

unsigned int VertexBuffer::boundId = 0;

VertexBuffer::VertexBuffer() : Buffer(GL_ARRAY_BUFFER) {}

void VertexBuffer::bind() const
{
    if (VertexBuffer::boundId != id)
    {
        Buffer::bind();
        boundId = id;
    }
}

void VertexBuffer::unbind() const
{
    if (VertexBuffer::boundId == id)
    {
        Buffer::unbind();
        boundId = 0;
    }
}
