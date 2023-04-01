#include<GL/glew.h>
#include<iostream>

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
"FragColor = mix(texture(myTexture1,TexCoord),texture(myTexture2,vec2(TexCoord.x,TexCoord.y)),transpancy);\n"
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
