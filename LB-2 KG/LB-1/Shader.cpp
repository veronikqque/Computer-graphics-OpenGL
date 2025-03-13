#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {

    std::string vertexSource = ReadFile(vertexPath);
    std::string fragmentSource = ReadFile(fragmentPath);

    GLuint vertexShaderID = CreateShader(GL_VERTEX_SHADER, vertexSource.c_str());
    GLuint fragmentShaderID = CreateShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());
    CreateProgram(vertexShaderID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::Activate() const {
    glUseProgram(ID);
}

void Shader::SetUniform(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::SetUniform(const std::string& name, float r, float g, float b, float a) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), r, g, b, a);
}

std::string Shader::ReadFile(const GLchar* filename) const {
    try {
        std::ifstream shaderFile(filename);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        return shaderStream.str();
    }
    catch (const std::ifstream::failure& e) {
        std::cerr << "ERROR: Unable to read shader file: " << filename << std::endl;
        return "";
    }
}

GLuint Shader::CreateShader(GLenum type, const char* sourceCode) const {

    GLuint shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &sourceCode, nullptr);
    glCompileShader(shaderID);

    GLint compileStatus;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus) {
        char infoLog[1024];
        glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR: Shader compilation failed\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    return shaderID;
}

void Shader::CreateProgram(GLuint vertexShaderID, GLuint fragmentShaderID) {
    ID = glCreateProgram();
    glAttachShader(ID, vertexShaderID);
    glAttachShader(ID, fragmentShaderID);
    glLinkProgram(ID);

    GLint linkStatus;
    glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        char infoLog[1024];
        glGetProgramInfoLog(ID, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR: Program linking failed\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
}
