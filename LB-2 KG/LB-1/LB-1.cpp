#define GLEW_DLL
#define GLFW_DLL

#include <iostream>
#include <stdio.h>
#include "glew.h"
#include "glfw3.h"
#include "Shader.h"

// Defining vertices for a square //
float vertexPositions[] = {
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
};

// Indexes for drawing two triangles //
GLuint vertexIndices[] = {
    0, 1, 2,
    0, 3, 2
};

int main() {
    // Initializing the GLFW library //
    if (!glfwInit()) {
        std::cerr << "ERROR: GLFW initialization failed." << std::endl;
        return -1;
    }

    // Configuring OpenGL settings //
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creating a window //
    GLFWwindow* window = glfwCreateWindow(512, 512, "Square", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    // Initialization of GLEW //
    if (glewInit() != GLEW_OK) {
        std::cerr << "ERROR: GLEW initialization failed." << std::endl;
        return -1;
    }

    // Creating a VAO, VBO, and EBO //
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Filling VBO with vertex data //
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    // Filling EBO with indexes //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Creating a shader program //
    Shader shader("vert_shader.glsl", "frag_shader.glsl");

    // The main rendering cycle //
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.4f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float currentTime = static_cast<float>(glfwGetTime());
        float red = (sin(currentTime) / 2.0f) + 0.5f;
        float green = (cos(currentTime) / 2.0f) + 0.5f;
        float blue = (sin(currentTime + 3.14f) / 2.0f) + 0.5f;

        shader.Activate();
        shader.SetUniform("inputColor", red, green, blue, 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
