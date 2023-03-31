#pragma once
#include<GL/glew.h>
extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;
extern const char* fragmentShaderSource2;
extern const char* fragmentShaderSource3;
extern char* fragmentShaderSource4;
extern const char* fragmentShaderSource5;
unsigned int createShader(const char* src, GLenum type);