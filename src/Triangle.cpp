#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<std_image.h>



static const char* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location=2) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos,1.0);\n"
"TexCoord = aTexCoord;\n"
"}\0";

static const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\0";


static const char* fragmentShaderSource2 = "#version 330 core\n"
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


static const char* fragmentShaderSource4 = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 myColor;\n"
"void main(){\n"
"FragColor = vec4(myColor,1.0f);\n"
"}\0";


static const char* fragmentShaderSource5 = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D myTexture1;\n"
"uniform sampler2D myTexture2;\n"
"void main(){\n"
"FragColor = mix(texture(myTexture1,TexCoord),texture(myTexture2,TexCoord),0.4);\n"
"}\0";


unsigned int createShader(const char* src,GLenum type) {
    unsigned int shader;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    return shader;
}

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }



    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();


    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
             0.8f,  0.8f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
             0.8f, -0.8f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.8f, -0.8f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.8f,  0.8f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };


    unsigned int vs = createShader(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fs = createShader(fragmentShaderSource5, GL_FRAGMENT_SHADER);
    //unsigned int fs2 = createShader(fragmentShaderSource3, GL_FRAGMENT_SHADER);
    unsigned int program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glUseProgram(program);


    //std::cout << glGetUniformLocation(fs2, "myColor") << std::endl;


    char infoLog[512];
    int success;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fs, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }


    int width, height, nrChannels;
    const char* fileName = "D:\\openglcode\\demo1\\x64\\Debug\\container.jpg";
    unsigned char* pic;
    pic = stbi_load(fileName, &width, &height, &nrChannels,0);
    if (!pic){
        std::cout << pic << std::endl;
        return 0;
    }

    unsigned int vbo;
    unsigned int vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    unsigned int index[] = { 0,1,3,1,2,3 };
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    unsigned int textures[2];
    glGenTextures(2, textures);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pic);
    stbi_image_free(pic);
    int width2, height2, nrChannels2;
    const char* smileFace = "D:\\openglcode\\demo1\\src\\awesomeface.png";
    stbi_set_flip_vertically_on_load(true);
    unsigned char* smile;
    smile = stbi_load(smileFace, &width2, &height2, &nrChannels2, 0);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, smile);
    stbi_image_free(smile);



    std::cout << glGetUniformLocation(program, "myTexture1") << std::endl;
    glUniform1i(glGetUniformLocation(program, "myTexture1"), 0);
    glUniform1i(glGetUniformLocation(program, "myTexture2"), 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,*textures);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, *(textures + 1));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        
        glClear(GL_COLOR_BUFFER_BIT);
        //float curtme = glfwGetTime();
        //float greenValue = sin(curtme)+ 0.2f;
        //int vertexColorLocation = glGetUniformLocation(program, "myColor");
        //glUniform4f(vertexColorLocation, greenValue, greenValue+0.1f, greenValue+0.2f, 0.5f);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}




void twoTrianglesWithTwoColors() {
    unsigned int shaderPrograme = glCreateProgram();
    unsigned int shaderPrograme2 = glCreateProgram();
    unsigned int vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fs1 = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    unsigned int fs2 = createShader(fragmentShaderSource2, GL_FRAGMENT_SHADER);
    glAttachShader(shaderPrograme, vertexShader);
    glAttachShader(shaderPrograme, fs1);
    glLinkProgram(shaderPrograme);
    glAttachShader(shaderPrograme2, vertexShader);
    glAttachShader(shaderPrograme2, fs2);
    glLinkProgram(shaderPrograme2);


    float firstTriangle[12] = {
        0.0f,0.5f,0.0f,
        0.0f,-0.5f,0.0f,
        -0.5f,0.0f,0.0f
    };
    float secondTrianle[12] = {
        0.0f,0.5f,0.0f,
        0.0f,-0.5f,0.0f,
        0.5f,0.0f,0.0f
    };

    unsigned int vertexBuffers[2];
    unsigned int vaos[2];
    glGenBuffers(2, vertexBuffers);
    glGenVertexArrays(2, vaos);
    glBindVertexArray(vaos[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(vaos[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTrianle), secondTrianle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void practice1() {
    unsigned int vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    unsigned int shaderProgram1;
    shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader);
    glLinkProgram(shaderProgram1);
    glUseProgram(shaderProgram1);


    float locations[18] = {
        -0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.75f,-0.5f,0.0f,
        1.0f,0.5f,0.0f
    };


    unsigned int drawIndex[6] = {
        0,1,2,3,4,5
    };

    unsigned int buffer;
    unsigned int vao;
    unsigned int ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &buffer);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(drawIndex), drawIndex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(locations), locations, GL_STATIC_DRAW);
}