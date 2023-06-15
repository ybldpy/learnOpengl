#pragma once
#define GLEW_STATIC
#include<GL/glew.h>
#include<iostream>
#include "shaders.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location=2) in vec2 aTexCoord;\n"
"uniform float offset;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x+offset,aPos.y,aPos.z,1.0);\n"
"TexCoord = aTexCoord;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\0";
const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"FragColor = vec4(1.0f,0.3f,0.2f,1.0f);\n"
"}\0";


static const char* fragmentShaderSource3 = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 myColor;\n"
"layout(location = 1) in vec3 aColor;\n"
"out vec4 FragColor;"
"void main(){\n"
"FragColor = vec4(aColor,1.0f);\n"
"}\0";


const char* fragmentShaderSource4 = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 myColor;\n"
"void main(){\n"
"FragColor = vec4(myColor,1.0f);\n"
"}\0";


const char* fragmentShaderSource5 = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D myTexture1;\n"
"uniform sampler2D myTexture2;\n"
"uniform float transpancy;\n"
"void main(){\n"
"FragColor = mix(texture(myTexture1,TexCoord),texture(myTexture2,vec2(TexCoord.x,TexCoord.y)),0.2);\n"
"}\0";


const char* fragmentShaderSource6 = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D myTexture1;\n"
"uniform float transpancy;\n"
"void main(){\n"
"FragColor = texture(myTexture1,TexCoord);\n"
"}\0";

const char* transformationVertexShader = "#version 330 core\n;"
"layout (location=0) in vec3 aPos;\n"
"layout (location=1) in vec2 aTexCoord;\n"
"uniform mat4 transform;\n"
"out vec2 TexCoord;"
"void main(){\n"
"gl_Position = transform*vec4(aPos,1.0);\n"
"TexCoord = aTexCoord;\n"
"}\0";


const char* threeDVertexShader = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"layout (location=1) in vec2 aTexCoord;"
"uniform mat4 transform;\n"
"out vec2 TexCoord;"
"void main(){\n"
"gl_Position = transform*vec4(aPos,1.0);\n"
"TexCoord = aTexCoord;\n"
"}\0";

const char* vertexShaderSrc1="#version 330 core\n"
                            "layout(location=0) in vec3 aPos;\n"
                            "layout(location=1) in vec2 aTexCoord;\n"
                            "uniform mat4 transformMatrix;\n"
                            "out vec2 TexCoord;"
                            "void main(){\n"
                            "gl_Position = transformMatrix*vec4(aPos,1.0);\n"
                            "TexCoord = aTexCoord;\n"
                            "}\0";

const char* light_cube_shader = "#version 330 core\n"
                                "uniform vec3 light_color;\n"
                                "uniform vec3 object_color;\n"
                                "out vec4 FragColor;\n"
                                "int main(){\n"
                                "FragColor = vec4(light_color*object_color,1.0);\n}";
const char* light_shader = "#version 330 core;\n"
                           "out vec4 FragColor;\n"
                           "int main(){\n"
                           "FragColor = vec4(1.0);\n"
                           "}"

const char* containerSrc = "D:\\openglcode\\demo1\\src\\container.jpg";
const char* faceSrc = "D:\\openglcode\\demo1\\src\\awesomeface.png";
unsigned int createShader(const char* src, GLenum type) {
    unsigned int shader;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    char infoLog[512];
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }
    return shader;
}





int Shader::getId() {
    return id;
}



    Shader::Shader(const char* shaderSrc,GLenum type){
        this->id = glCreateShader(type);
        glShaderSource(this->id,1,&shaderSrc,NULL);
        glCompileShader(this->id);
        glGetShaderiv(this->id,GL_COMPILE_STATUS,&success);
        if (!success){
            glGetShaderInfoLog(this->id,infoLen,NULL,infoLog);
            std::cout<<infoLog<<std::endl;
        }
    }


    void Shader::attach(unsigned int pid){
        glAttachShader(pid,this->id);
    }

    void Shader::deleteShader(){
        glDeleteShader(this->id);
    }

    void Shader::setInt(const char* name,int value,unsigned int pid){
        glUniform1i(glGetUniformLocation(pid,name),value);
    }
    void Shader::setBool(const char* name,bool value,unsigned int pid){
        setInt(name,value,pid);
    }
    void Shader::setFloat(const char* name,float value,unsigned int pid){
        glUniform1f(glGetUniformLocation(pid,name),value);
    }


