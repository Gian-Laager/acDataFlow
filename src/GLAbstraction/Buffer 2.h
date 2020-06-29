#pragma once

#include "pch.h"

class Buffer
{
protected:
    GLenum target;

public:
    unsigned int id;
    Buffer(GLenum target);

    virtual void data(void* data, unsigned int size, GLenum usage);

    virtual void bind() const;

    virtual void unbind() const;

    virtual Buffer operator=(const Buffer&) = delete;

    ~Buffer();
};