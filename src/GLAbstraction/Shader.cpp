#include "Shader.h"

#include <utility>

unsigned int Shader::boundId = 0;

ShaderProgramSources::ShaderProgramSources(std::string vertexSource, std::string fragmentSource)
        : vertexSource(std::move(
        vertexSource)), fragmentSource(std::move(fragmentSource)) {}

ShaderProgramSources* Shader::parseShader(const std::string &filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        } else
        {
            ss[(int) type] << line << '\n';
        }
    }

    return new ShaderProgramSources(ss[0].str(), ss[1].str());
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source)
{
    glCall(unsigned int t_id = glCreateShader(type));
    const char* src = source.c_str();
    glCall(glShaderSource(t_id, 1, &src, nullptr));
    glCall(glCompileShader(t_id));

    int result;
    glCall(glGetShaderiv(t_id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        glCall(glGetShaderiv(t_id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*) alloca(length * sizeof(char));
        glCall(glGetShaderInfoLog(t_id, length, &length, message));
        std::cout << "Failed to compile shader, message: " << message << std::endl;
        glCall(glDeleteProgram(t_id));
        return 0;
    }

    return t_id;
}

unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int vs = Shader::compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = Shader::compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glCall(unsigned int program = glCreateProgram());
    
    glCall(glAttachShader(program, vs));
    glCall(glAttachShader(program, fs));
    glCall(glLinkProgram(program));

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        char* infoLog = new char[maxLength];
        glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

        std::cout << "something with the shader program went wrong: " << infoLog << std::endl;

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        glDeleteShader(vs);
        glDeleteShader(fs);

        throw std::string("something with the shader program went wrong: ") + std::string(infoLog);
    }
    glCall(glValidateProgram(program));

    glCall(glDetachShader(program, vs));
    glCall(glDetachShader(program, fs));

    return program;
}

Shader::Shader(const char* filePath) : id(0)
{
    ShaderProgramSources* shaderSource = Shader::parseShader(filePath);
    id = Shader::createShader(shaderSource->vertexSource, shaderSource->fragmentSource);
    delete shaderSource;
}

void Shader::bind() const
{
    if (Shader::boundId != id)
    {
        glCall(glUseProgram(id));
        Shader::boundId = id;
    }
}

void Shader::unbind() const
{
    if (Shader::boundId == id)
    {
        glCall(glUseProgram(0));
        Shader::boundId = 0;
    }
}

int Shader::getUniformLocation(const char* attribName) const
{
    bind();
    glCall(int retV = glGetUniformLocation(id, attribName));
    return retV;
}

int Shader::getAttribLocation(const char* attribName) const
{
    bind();
    glCall(int retV = glGetAttribLocation(id, attribName));
    unbind();
    return retV;
}

void Shader::setUniform2i(const char* uniformName, int v0, int v1)
{
    bind();
    glCall(glUniform2i(getUniformLocation(uniformName), v0, v1));
    unbind();
}

void Shader::setUniform3i(const char* uniformName, int v0, int v1, int v2)
{
    bind();
    glCall(glUniform3i(getUniformLocation(uniformName), v0, v1, v2));
    unbind();
}

void Shader::setUniform1f(const char* uniformName, float v0)
{
    bind();
    glCall(glUniform1f(getUniformLocation(uniformName), v0));
    unbind();
}

void Shader::setUniform2f(const char* uniformName, float v0, float v1)
{
    bind();
    glCall(glUniform2f(getUniformLocation(uniformName), v0, v1));
    unbind();
}

void Shader::setUniform3f(const char* uniformName, float v0, float v1, float v2)
{
    bind();
    glCall(glUniform3f(getUniformLocation(uniformName), v0, v1, v2));
    unbind();
}

void Shader::setUniform4f(const char* uniformName, float v0, float v1, float v2, float v3)
{
    bind();
    glCall(glUniform4f(getUniformLocation(uniformName), v0, v1, v2, v3));
    unbind();
}

void Shader::setUniform1i(const char* uniformName, int v0)
{
    bind();
    glCall(glUniform1i(getUniformLocation(uniformName), v0));
    unbind();
}

void Shader::setUniform4i(const char* uniformName, int v0, int v1, int v2, int v3)
{
    bind();
    glCall(glUniform4i(getUniformLocation(uniformName), v0, v1, v2, v3));
    unbind();
}

void Shader::setUniform1ui(const char* uniformName, unsigned int v0)
{
    bind();
    glCall(glUniform1ui(getUniformLocation(uniformName), v0));
    unbind();
}

void Shader::setUniform2ui(const char* uniformName, unsigned int v0, unsigned int v1)
{
    bind();
    glCall(glUniform2ui(getUniformLocation(uniformName), v0, v1));
    unbind();
}

void Shader::setUniform3ui(const char* uniformName, unsigned int v0, unsigned int v1, unsigned int v2)
{
    bind();
    glCall(glUniform3ui(getUniformLocation(uniformName), v0, v1, v2));
    unbind();
}

void
Shader::setUniform4ui(const char* uniformName, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3)
{
    bind();
    glCall(glUniform4ui(getUniformLocation(uniformName), v0, v1, v2, v3));
    unbind();
}

void Shader::setUniform1fv(const char* uniformName, int count, const float* value)
{
    bind();
    glCall(glUniform1fv(getUniformLocation(uniformName), count, value));
    unbind();
}

void Shader::setUniform2fv(const char* uniformName, int count, const float* value)
{
    bind();
    glCall(glUniform2fv(getUniformLocation(uniformName), count, value));
    unbind();
}

void Shader::setUniform3fv(const char* uniformName, int count, const float* value)
{
    bind();
    glCall(glUniform3fv(getUniformLocation(uniformName), count, value));
    unbind();
}

void Shader::setUniform4fv(const char* uniformName, int count, const float* value)
{
    bind();
    glCall(glUniform4fv(getUniformLocation(uniformName), count, value));
    unbind();
}

void Shader::setUniform1iv(const char* uniformName, int count, const int* value)
{
    bind();
    glCall(glUniform1iv(getUniformLocation(uniformName), count, value));
    unbind();
}

void Shader::setUniform2iv(const char* uniformName, int count, const int* value)
{
    bind();
    glCall(glUniform2iv(getUniformLocation(uniformName), count, value));
    unbind();
}

void Shader::setUniform3iv(const char* uniformName, int count, const int* value)
{
    bind();
    glCall(glUniform3iv(getUniformLocation(uniformName), count, value));
    unbind();
}

void Shader::setUniform4iv(const char* uniformName, int count, const int* value)
{
    bind();
    glCall(glUniform4iv(getUniformLocation(uniformName), count, value));
    unbind();
}

void Shader::setUniform1uiv(const char* uniformName, int count, const unsigned int* value)
{
    bind();
    glCall(glUniform4uiv(getUniformLocation(uniformName), count, value));
    unbind();
}

void Shader::setUniform2uiv(const char* uniformName, int count, const unsigned int* value)
{
    bind();
    glCall(glUniform2uiv(getUniformLocation(uniformName), count, value));
    unbind();
}

void Shader::setUniform3uiv(const char* uniformName, int count, const unsigned int* value)
{
    bind();
    glCall(glUniform3uiv(getUniformLocation(uniformName), count, value));
    unbind();
}

void Shader::setUniform4uiv(const char* uniformName, int count, const unsigned int* value)
{
    bind();
    glCall(glUniform4uiv(getUniformLocation(uniformName), count, value));
    unbind();
}

void Shader::setUniformMatrix2fv(const char* uniformName, int count, bool transpose, const float* value)
{
    bind();
    glCall(glUniformMatrix2fv(getUniformLocation(uniformName), count, transpose, value));
    unbind();
}

void Shader::setUniformMatrix3fv(const char* uniformName, int count, bool transpose, const float* value)
{
    bind();
    glCall(glUniformMatrix3fv(getUniformLocation(uniformName), count, transpose, value));
    unbind();
}

void Shader::setUniformMatrix4fv(const char* uniformName, int count, bool transpose, const float* value)
{
    bind();
    glCall(glUniformMatrix4fv(getUniformLocation(uniformName), count, transpose, value));
    unbind();
}

void Shader::setUniformMatrix2x3fv(const char* uniformName, int count, bool transpose, const float* value)
{
    bind();
    glCall(glUniformMatrix2x3fv(getUniformLocation(uniformName), count, transpose, value));
    unbind();
}

void Shader::setUniformMatrix3x2fv(const char* uniformName, int count, bool transpose, const float* value)
{
    bind();
    glCall(glUniformMatrix3x2fv(getUniformLocation(uniformName), count, transpose, value));
    unbind();
}

void Shader::setUniformMatrix2x4fv(const char* uniformName, int count, bool transpose, const float* value)
{
    bind();
    glCall(glUniformMatrix2x4fv(getUniformLocation(uniformName), count, transpose, value));
    unbind();
}

void Shader::setUniformMatrix4x2fv(const char* uniformName, int count, bool transpose, const float* value)
{
    bind();
    glCall(glUniformMatrix4x2fv(getUniformLocation(uniformName), count, transpose, value));
    unbind();
}

void Shader::setUniformMatrix3x4fv(const char* uniformName, int count, bool transpose, const float* value)
{
    bind();
    glCall(glUniformMatrix3x4fv(getUniformLocation(uniformName), count, transpose, value));
    unbind();
}

void Shader::setUniformMatrix4x3fv(const char* uniformName, int count, bool transpose, const float* value)
{
    bind();
    glCall(glUniformMatrix4x3fv(getUniformLocation(uniformName), count, transpose, value));
    unbind();
}