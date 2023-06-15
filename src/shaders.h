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
extern const char* vertexShaderSrc1;
extern const char* light_shader;
extern const char* light_cube_shader;
unsigned int createShader(const char* src, GLenum type);
class Shader{
private:
    unsigned int id;
    int success;
    char infoLog[512];
    const int infoLen = 512;
public:
    Shader(const char* shaderSrc,GLenum type);
    int getId();
    void attach(unsigned int pid);
    void setInt(const char* name,int value,unsigned int pid);
    void setBool(const char* name,bool value,unsigned int pid);
    void setFloat(const char* name,float value,unsigned int pid);
    void deleteShader();
};
