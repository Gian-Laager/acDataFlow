#pragma once

#include "Buffer.h"

class VertexBuffer : public Buffer
{
public:
    static unsigned int boundId;
    VertexBuffer();

    void bind() const override;
    void unbind() const override;
};