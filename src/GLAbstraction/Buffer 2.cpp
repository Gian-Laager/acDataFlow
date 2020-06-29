#include "Buffer.h"

Buffer::Buffer(GLenum target) : target(target)
{
    glCall(glGenBuffers(1, &id));
}

void Buffer::data(void* data, unsigned int size, GLenum usage)
{
    bind();
    glCall(glBufferData(target, size, data, usage));
    unbind();
}

void Buffer::bind() const
{
        glCall(glBindBuffer(target, id));
}

void Buffer::unbind() const
{
        glCall(glBindBuffer(target, 0));
}

Buffer::~Buffer()
{
    glCall(glDeleteBuffers(1, &id));
}