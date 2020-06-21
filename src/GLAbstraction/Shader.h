#pragma once

#include "pch.h"

struct ShaderProgramSources {
    std::string vertexSource, fragmentSource;

    ShaderProgramSources(std::string vertexSource, std::string fragmentSource);
};

class Shader {
public:
    static unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);

    static unsigned int compileShader(unsigned int type, const std::string &source);

    static ShaderProgramSources* parseShader(const std::string &filePath);

    unsigned int id;

    static unsigned int boundId;

    Shader(const char* filePath);

    void bind() const;

    void unbind() const;

    int getUniformLocation(const char* attribName) const;
    
    int getAttribLocation(const char* attribName) const;

    void setUniform1f(const char* uniformName,
                      float v0);

    void setUniform2f(const char* uniformName,
                      float v0,
                      float v1);

    void setUniform3f(const char* uniformName,
                      float v0,
                      float v1,
                      float v2);

    void setUniform4f(const char* uniformName,
                      float v0,
                      float v1,
                      float v2,
                      float v3);

    void setUniform1i(const char* uniformName,
                      int v0);

    void setUniform2i(const char* uniformName,
                      int v0,
                      int v1);

    void setUniform3i(const char* uniformName,
                      int v0,
                      int v1,
                      int v2);

    void setUniform4i(const char* uniformName,
                      int v0,
                      int v1,
                      int v2,
                      int v3);

    void setUniform1ui(const char* uniformName,
                       unsigned int v0);

    void setUniform2ui(const char* uniformName,
                       unsigned int v0,
                       unsigned int v1);

    void setUniform3ui(const char* uniformName,
                       unsigned int v0,
                       unsigned int v1,
                       unsigned int v2);

    void setUniform4ui(const char* uniformName,
                       unsigned int v0,
                       unsigned int v1,
                       unsigned int v2,
                       unsigned int v3);

    void setUniform1fv(const char* uniformName,
                       int count,
                       const float* value);

    void setUniform2fv(const char* uniformName,
                       int count,
                       const float* value);

    void setUniform3fv(const char* uniformName,
                       int count,
                       const float* value);

    void setUniform4fv(const char* uniformName,
                       int count,
                       const float* value);

    void setUniform1iv(const char* uniformName,
                       int count,
                       const int* value);

    void setUniform2iv(const char* uniformName,
                       int count,
                       const int* value);

    void setUniform3iv(const char* uniformName,
                       int count,
                       const int* value);

    void setUniform4iv(const char* uniformName,
                       int count,
                       const int* value);

    void setUniform1uiv(const char* uniformName,
                        int count,
                        const unsigned int* value);

    void setUniform2uiv(const char* uniformName,
                        int count,
                        const unsigned int* value);

    void setUniform3uiv(const char* uniformName,
                        int count,
                        const unsigned int* value);

    void setUniform4uiv(const char* uniformName,
                        int count,
                        const unsigned int* value);

    void setUniformMatrix2fv(const char* uniformName,
                             int count,
                             bool transpose,
                             const float* value);

    void setUniformMatrix3fv(const char* uniformName,
                             int count,
                             bool transpose,
                             const float* value);

    void setUniformMatrix4fv(const char* uniformName,
                             int count,
                             bool transpose,
                             const float* value);

    void setUniformMatrix2x3fv(const char* uniformName,
                               int count,
                               bool transpose,
                               const float* value);

    void setUniformMatrix3x2fv(const char* uniformName,
                               int count,
                               bool transpose,
                               const float* value);

    void setUniformMatrix2x4fv(const char* uniformName,
                               int count,
                               bool transpose,
                               const float* value);

    void setUniformMatrix4x2fv(const char* uniformName,
                               int count,
                               bool transpose,
                               const float* value);

    void setUniformMatrix3x4fv(const char* uniformName,
                               int count,
                               bool transpose,
                               const float* value);

    void setUniformMatrix4x3fv(const char* uniformName,
                               int count,
                               bool transpose,
                               const float* value);

};