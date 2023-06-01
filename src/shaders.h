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
extern const char* threeDVertexShader;
extern const char* containerSrc;
extern const char* faceSrc;
unsigned int createShader(const char* src, GLenum type);
