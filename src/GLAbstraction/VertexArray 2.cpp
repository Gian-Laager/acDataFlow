#include "VertexArray.h"

unsigned int VertexArray::boundId = 0;

void VertexArray::push(const IndexBuffer* buffer)
{
    bind();
    buffer->bind();
    unbind();
    buffer->unbind();
    isIndexBuffer = true;
}

void VertexArray::bind() const
{
    if (VertexArray::boundId != id)
    {
        VertexArray::boundId = id;
        glCall(glBindVertexArray(id));
        enableAll();
    }
}

void VertexArray::unbind() const
{
    if (boundId == id)
    {
        disableAll();
        glCall(glBindVertexArray(0));
        VertexArray::boundId = 0;
    }
}

void VertexArray::push(const VertexBuffer* buffer, const VertexBufferLayout layouts[], unsigned int numberOfLayouts)
{
    bind(false);
    buffer->bind();
    for (int i = 0; i < numberOfLayouts; i++)
    {
        indecies.insert(layouts[i].attribIndex);
        glCall(glEnableVertexAttribArray(layouts[i].attribIndex));
        glCall(glVertexAttribPointer(layouts[i].attribIndex, layouts[i].numberOfElements, layouts[i].type,
                                     layouts[i].normalized, layouts[i].stride, layouts[i].memberOffset));
    }
    buffer->unbind();
    unbind();
}

VertexArray::VertexArray()
{
    glCall(glGenVertexArrays(1, &id));
}

void VertexArray::disableAll() const
{
    std::set<unsigned int>::iterator itr;
    for (itr = indecies.begin(); itr != indecies.end(); ++itr)
    {
        glCall(glDisableVertexAttribArray(*itr));
    }
}

void VertexArray::enableAll() const
{
    std::set<unsigned int>::iterator itr;
    for (itr = indecies.begin(); itr != indecies.end(); ++itr)
    {
        glCall(glEnableVertexAttribArray(*itr));
    }
}

void VertexArray::unbind(bool disableAll) const
{
    if (disableAll)
    {
        unbind();
    }
    else
    {
        if (boundId == id)
        {
            glCall(glBindVertexArray(0));
            VertexArray::boundId = 0;
        }
    }
}

void VertexArray::bind(bool enableAll) const
{
    if (enableAll)
    {
        bind();
    }
    else
    {
        if (boundId != id)
        {
            glCall(glBindVertexArray(id));
            VertexArray::boundId = id;
        }
    }
}
