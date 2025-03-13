#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glew.h>

class Shader {
public:
    GLuint ID;

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader();

    void Activate() const;

    void SetUniform(const std::string& name, float value) const;
    void SetUniform(const std::string& name, int value) const;
    void SetUniform(const std::string& name, float x, float y, float z) const;
    void SetUniform(const std::string& name, float r, float g, float b, float a) const;

private:
    std::string ReadFile(const GLchar* filename) const;
    GLuint CreateShader(GLenum type, const char* source) const;
    void CreateProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
};

#endif
