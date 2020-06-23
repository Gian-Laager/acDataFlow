#include "Renderer.h"

void GLErrorHandling::clearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLErrorHandling::logCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::stringstream errorIdHex;
        errorIdHex << std::hex << error;
        std::cout << "[OpenGL Error] (" << errorIdHex.str() << ") " << "file: " << file << ":" << line << " function: "
                  << function << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer(VertexArray* vao, Shader* shader) : shader(shader), vao(vao), drawMode(DrawMode::VERTEX_ARRAY) {}


Renderer::Renderer(VertexBuffer* vbo, VertexBufferLayout* layouts, unsigned int numberOfLayouts,
                   Shader* shader) : shader(shader),
                                     vbo(vbo),
                                     drawMode(
                                             DrawMode::VERTEX_BUFFER), numberOfLayouts(numberOfLayouts),
                                     layouts(layouts) {}

Renderer::Renderer(VertexBuffer* vbo, IndexBuffer* ibo, VertexBufferLayout* layouts, unsigned int numberOfLayouts,
                   Shader* shader) : shader(shader),
                                     vbo(vbo),
                                     ibo(ibo),
                                     drawMode(
                                             DrawMode::VERTEX_AND_INDEX_BUFFER), numberOfLayouts(numberOfLayouts),
                                     layouts(layouts) {}


void Renderer::draw(int numberOfVertecies)
{
    switch (drawMode)
    {
        case DrawMode::VERTEX_ARRAY :
        {
            vao->bind();
            shader->bind();
            if (vao->isIndexBuffer)
            {
                glCall(glDrawElements(GL_TRIANGLES, numberOfVertecies, GL_UNSIGNED_INT, nullptr));
            } else
            {
                glCall(glDrawArrays(GL_TRIANGLES, (int) (((long) nullptr) / sizeof(unsigned int)),
                                    numberOfVertecies));
            }
            vao->unbind();
            shader->unbind();
            break;
        }
        case DrawMode::VERTEX_BUFFER :
        {
            VertexArray temp_va;
            temp_va.push(vbo, layouts, numberOfLayouts);
            temp_va.bind();
            shader->bind();
            glCall(glDrawArrays(GL_TRIANGLES, 0, numberOfVertecies));
            shader->unbind();
            temp_va.unbind();
            break;
        }

        case DrawMode::VERTEX_AND_INDEX_BUFFER :
        {
            draw();
            break;
        }
    }
}

void Renderer::draw(int numberOfVertecies, void* offset)
{
    switch (drawMode)
    {
        case DrawMode::VERTEX_ARRAY :
        {
            vao->bind();
            shader->bind();
            if (vao->isIndexBuffer)
            {
                glCall(glDrawElements(GL_TRIANGLES, numberOfVertecies, GL_UNSIGNED_INT, offset));
            } else
            {
                glCall(glDrawArrays(GL_TRIANGLES, (int) (((long) offset) / sizeof(unsigned int)),
                                    numberOfVertecies));
            }
            shader->unbind();
            vao->unbind();
            break;
        }
        case DrawMode::VERTEX_BUFFER :
        {
            VertexArray temp_va;
            temp_va.push(vbo, layouts, numberOfLayouts);
            temp_va.bind();
            shader->bind();
            glCall(glDrawArrays(GL_TRIANGLES, (int) (((long) offset) / sizeof(unsigned int)), numberOfVertecies));
            shader->unbind();
            temp_va.unbind();
            break;
        }

        case DrawMode::VERTEX_AND_INDEX_BUFFER :
        {
            draw(offset);
            break;
        }
    }
}

void Renderer::draw()
{
    if (drawMode != DrawMode::VERTEX_AND_INDEX_BUFFER)
        throw "you have to use the constructor 'Renderer::Renderer(VertexBuffer* vbo, IndexBuffer* ibo, Shader* shader)' to use that function or use 'Renderer::draw(unsigned int numberOfVertecies)' instead.";

    VertexArray temp_va;
    temp_va.push(ibo);
    temp_va.push(vbo, layouts, numberOfLayouts);
    temp_va.bind();
    shader->bind();
    glCall(glDrawElements(GL_TRIANGLES, ibo->numberOfVertecies, GL_UNSIGNED_INT, nullptr));
    shader->unbind();
    temp_va.unbind();
}

void Renderer::draw(void* offset)
{
    if (drawMode != DrawMode::VERTEX_AND_INDEX_BUFFER)
        throw "you have to use the constructor 'Renderer::Renderer(VertexBuffer* vbo, IndexBuffer* ibo, Shader* shader)' to use that function or use 'Renderer::draw(unsigned int numberOfVertecies)' instead.";

    VertexArray temp_va;
    temp_va.push(ibo);
    temp_va.push(vbo, layouts, numberOfLayouts);
    temp_va.bind();
    shader->bind();
    glCall(glDrawElements(GL_TRIANGLES, ibo->numberOfVertecies, GL_UNSIGNED_INT, offset));
    shader->unbind();
    temp_va.unbind();
}

void Renderer::draw(unsigned int numberOfVertecies, GLenum mode)
{
    switch (drawMode)
    {
        case DrawMode::VERTEX_ARRAY :
        {
            vao->bind();
            shader->bind();
            if (vao->isIndexBuffer)
            {
                glCall(glDrawElements(mode, numberOfVertecies, GL_UNSIGNED_INT, nullptr));
            } else
            {
                glCall(glDrawArrays(mode, (int) (((long) nullptr) / sizeof(unsigned int)), numberOfVertecies));
            }
            shader->unbind();
            vao->unbind();
            break;

            case DrawMode::VERTEX_BUFFER :
            {
                VertexArray temp_va;
                temp_va.push(vbo, layouts, numberOfLayouts);
                temp_va.bind();
                shader->bind();
                glCall(glDrawArrays(mode, (int) (((long) nullptr) / sizeof(unsigned int)), numberOfVertecies));
                shader->unbind();
                temp_va.unbind();
                break;
            }

            case DrawMode::VERTEX_AND_INDEX_BUFFER :
            {
                draw(nullptr);
                break;
            }
        }
    }
}

void Renderer::draw(GLenum mode)
{
    if (drawMode != DrawMode::VERTEX_AND_INDEX_BUFFER)
        throw "you have to use the constructor 'Renderer::Renderer(VertexBuffer* vbo, IndexBuffer* ibo, Shader* shader)' to use that function or use 'Renderer::draw(unsigned int numberOfVertecies)' instead.";

    VertexArray temp_va;
    temp_va.push(ibo);
    temp_va.push(vbo, layouts, numberOfLayouts);
    temp_va.bind();
    shader->bind();
    glCall(glDrawElements(mode, ibo->numberOfVertecies, GL_UNSIGNED_INT, nullptr));
    shader->unbind();
    temp_va.unbind();
}

void Renderer::draw(void* offset, GLenum mode)
{
    if (drawMode != DrawMode::VERTEX_AND_INDEX_BUFFER)
        throw "you have to use the constructor 'Renderer::Renderer(VertexBuffer* vbo, IndexBuffer* ibo, Shader* shader)' to use that function or use 'Renderer::draw(unsigned int numberOfVertecies)' instead.";

    VertexArray temp_va;
    temp_va.push(ibo);
    temp_va.push(vbo, layouts, numberOfLayouts);
    temp_va.bind();
    shader->bind();
    glCall(glDrawElements(mode, ibo->numberOfVertecies, GL_UNSIGNED_INT, offset));
    shader->unbind();
    temp_va.unbind();
}

void Renderer::draw(int numberOfVertecies, void* offset, GLenum mode)
{
    switch (drawMode)
    {
        case DrawMode::VERTEX_ARRAY :
        {
            vao->bind();
            shader->bind();
            if (vao->isIndexBuffer)
            {
                glCall(glDrawElements(mode, numberOfVertecies, GL_UNSIGNED_INT, offset));
            } else
            {
                glCall(glDrawArrays(mode, (int) (((long) offset) / sizeof(unsigned int)), numberOfVertecies));
            }
            shader->unbind();
            vao->unbind();
            break;
        }
        case DrawMode::VERTEX_BUFFER :
        {
            VertexArray temp_va;
            temp_va.push(vbo, layouts, numberOfLayouts);
            temp_va.bind();
            shader->bind();
            glCall(glDrawArrays(mode, (int) (((long) offset) / sizeof(unsigned int)), numberOfVertecies));
            shader->unbind();
            temp_va.unbind();
            break;
        }

        case DrawMode::VERTEX_AND_INDEX_BUFFER :
        {
            draw(offset);
            break;
        }
    }
}
