#pragma once
#include<GL/glew.h>
extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;
extern const char* fragmentShaderSource2;
extern const char* fragmentShaderSource3;
extern const char* fragmentShaderSource4;
extern const char* fragmentShaderSource5;
extern const char* fragmentShaderSource6;
extern const char* transformationVertexShader;


unsigned int createShader(const char* src, GLenum type);