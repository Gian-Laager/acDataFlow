#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout(const char* attribName, const Shader* shader, unsigned int numberOfElements,
                                       GLenum type,
                                       bool normalized, unsigned int stride,
                                       void* memberOffset) : numberOfElements(numberOfElements), type(type),
                                                             normalized(normalized), stride(stride),
                                                             memberOffset(memberOffset)
{
    attribIndex = shader->getAttribLocation(attribName);
}

VertexBufferLayout::VertexBufferLayout(int attribIndex, unsigned int numberOfElements, GLenum type,
                                       bool normalized, unsigned int stride,
                                       void* memberOffset) : attribIndex(attribIndex),
                                                             numberOfElements(numberOfElements), type(type),
                                                             normalized(normalized), stride(stride),
                                                             memberOffset(memberOffset) {}

VertexBufferLayout::~VertexBufferLayout()
{
    delete attribName;
}
