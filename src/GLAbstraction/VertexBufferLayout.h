#pragma once

#include "Shader.h"

class VertexBufferLayout {
public:
    const Shader* shader = nullptr;
    const char* attribName = nullptr;
    int attribIndex;
    unsigned int numberOfElements;
    GLenum type;
    bool normalized;
    unsigned int stride;
    void* memberOffset;

    VertexBufferLayout(const char* attribName, const Shader* shader, unsigned int numberOfElements, GLenum type,
                       bool normalized, unsigned int stride, void* memberOffset);

    VertexBufferLayout(int attribIndex, unsigned int numberOfElements, GLenum type, bool normalized, unsigned int stride,
                       void* memberOffset);
};

