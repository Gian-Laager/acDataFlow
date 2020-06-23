#include "IndexBuffer.h"

unsigned int IndexBuffer::boundId = 0;

IndexBuffer::IndexBuffer(int numberOfVertecies) : Buffer(GL_ELEMENT_ARRAY_BUFFER), numberOfVertecies(numberOfVertecies) {}

void IndexBuffer::bind() const
{
    if (IndexBuffer::boundId != id)
    {
        Buffer::bind();
        IndexBuffer::boundId = id;
    }
}

void IndexBuffer::unbind() const
{
    if (IndexBuffer::boundId == id)
    {
        Buffer::unbind();
        IndexBuffer::boundId = 0;
    }
}

