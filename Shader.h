#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glew.h"

class Shader {
public:
    GLuint Program;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Use() const;

    void SetUniform(const std::string& name, float value) const;
    void SetUniform(const std::string& name, int value) const;
    void SetUniform(const std::string& name, float x, float y, float z) const;
    void SetUniform(const std::string& name, float r, float g, float b, float a) const;
    void SetUniform(const std::string& name, const float* matrix) const;

private:
    std::string ReadFile(const char* filename) const;
    GLuint CompileShader(GLenum type, const char* source) const;
    void LinkProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
};

#endif
