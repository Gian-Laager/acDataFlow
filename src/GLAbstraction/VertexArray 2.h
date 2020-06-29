#pragma once

#include "pch.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
public:
    unsigned int id;

    static unsigned int boundId;

    std::set<unsigned int> indecies;

    bool isIndexBuffer = false;

    VertexArray();

    void push(const IndexBuffer* buffer);

    void push(const VertexBuffer* buffer, const VertexBufferLayout* layouts, unsigned int numberOfLayouts);

    void bind() const;
    void unbind() const;

    void bind(bool enableAll) const;
    void unbind(bool disableAll) const;

    virtual VertexArray operator=(const VertexArray&) = delete;

private:
    void disableAll() const;

    void enableAll() const;
};