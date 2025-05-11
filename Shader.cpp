#include "Shader.h"


Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {

    std::string vertexCode = ReadFile(vertexPath);
    std::string fragmentCode = ReadFile(fragmentPath);


    GLuint vertex = CompileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
    LinkProgram(vertex, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(Program);
}

void Shader::Use() const {
    glUseProgram(Program);
}

void Shader::SetUniform(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(Program, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(Program, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(Program, name.c_str()), x, y, z);
}

void Shader::SetUniform(const std::string& name, float r, float g, float b, float a) const {
    glUniform4f(glGetUniformLocation(Program, name.c_str()), r, g, b, a);
}

void Shader::SetUniform(const std::string& name, const float* matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(Program, name.c_str()), 1, GL_FALSE, matrix);
}


std::string Shader::ReadFile(const GLchar* filename) const {
    try {
        std::ifstream file(filename);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    catch (const std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << filename << std::endl;
        return "";
    }
}

GLuint Shader::CompileShader(GLenum type, const char* source) const {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
    return shader;
}

void Shader::LinkProgram(GLuint vertex, GLuint fragment) {
    Program = glCreateProgram();
    glAttachShader(Program, vertex);
    glAttachShader(Program, fragment);
    glLinkProgram(Program);

    GLint success;
    glGetProgramiv(Program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(Program, 1024, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM_LINKING_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
}
