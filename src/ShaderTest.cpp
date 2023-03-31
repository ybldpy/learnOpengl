#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

unsigned int createShader(const char* src, GLenum type);


void shaderPractice() {
    float colorableTriangle[18] = {
        0.0f,0.5f,0.0f,1.0f,0.2f,0.3f,
        -0.5f,-0.5f,0.0f,0.0f,1.0f,0.4f,
        0.5f,-0.5f,0.0f,0.0f,0.0f,1.0f
    };

    unsigned int vs = createShader("vertexShaderSource", GL_VERTEX_SHADER);
    unsigned int fs = createShader("fragmentShaderSource4", GL_FRAGMENT_SHADER);
    unsigned int program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glUseProgram(program);
    char infoLog[512];
    int success;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fs, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }
    unsigned int vbo;
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorableTriangle), colorableTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0);
}