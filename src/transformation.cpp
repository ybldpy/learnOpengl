#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<iostream>
#include"shaders.h"
#include"std_image.h"



void review(){
    GLFWwindow* window;
    if (!glfwInit()){
        std::cout<<"Error"<<std::endl;
        return;
    }

    window = glfwCreateWindow(800,800,"D",NULL,NULL);
    if (!window){
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glewInit();

    Shader vs(vertexShaderSrc1,GL_VERTEX_SHADER);
    Shader fs(fragmentShaderSource6,GL_FRAGMENT_SHADER);
    unsigned int program = glCreateProgram();
    vs.attach(program);
    fs.attach(program);
    glLinkProgram(program);
    glUseProgram(program);
    vs.deleteShader();
    fs.deleteShader();

    unsigned int vbo,ebo;
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof (float),0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof (float),(void*)(3*sizeof (float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    float vertices[] = {
            0.5f,0.5f,0.0f,    1.0f,1.0f,
            0.5f,-0.5f,0.0f,   1.0f,0.0f,
            -0.5f,0.5f,0.0f,   0.0f,1.0f,
            -0.5f,-0.5f,0.0f,   0.0f,0.0f
    };
    unsigned int index[] = {
            0,1,2,
            2,1,3
    };
    glBufferData(GL_ARRAY_BUFFER,sizeof (vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof (index),index,GL_STATIC_DRAW);
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    int width,height,nrChannles;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* smile_face = stbi_load(faceSrc,&width,&height,&nrChannles,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, smile_face);
    stbi_image_free(smile_face);


    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 trans = glm::mat4 (1.0f);
        trans = glm::rotate(trans,(float)glfwGetTime(),glm::vec3(0.0f,0.0f,1.0f));
        trans = glm::scale(trans,glm::vec3(abs(sin(glfwGetTime())), abs(sin(glfwGetTime())), 1));
        unsigned int matLocation = glGetUniformLocation(program,"transformMatrix");
        glUniformMatrix4fv(matLocation,1,GL_FALSE,glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();





}


int transformationTest() {
	GLFWwindow* window;
	if (!glfwInit()) {
		return -1;
	}


	window = glfwCreateWindow(800, 800, "transformation", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewInit();

	unsigned int vs = createShader(transformationVertexShader, GL_VERTEX_SHADER);
	unsigned int fs = createShader(fragmentShaderSource6, GL_FRAGMENT_SHADER);
	unsigned int program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	unsigned int vbo;
	unsigned int ebo;
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	float vertices[] = {
		0.5f,0.5f,0.0f,    1.0f,1.0f,
		0.5f,-0.5f,0.0f,   1.0f,0.0f,
		-0.5f,0.5f,0.0f,   0.0f,1.0f,
		-0.5f,-0.5f,0.0f,   0.0f,0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	unsigned int index[] = {0,1,3,2,0,3};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	int width, height, nrChannles;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* smileFace = stbi_load(faceSrc, &width, &height, &nrChannles, 0);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, smileFace);
	stbi_image_free(smileFace);

	
	glUseProgram(program);
	float a = 0.0;
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glm::mat4 transformationMatrix = glm::mat4(1.0f);
		transformationMatrix = glm::scale(transformationMatrix, glm::vec3(a,a,a));
		if (a < 1.0f) { a+=0.01f; }
		transformationMatrix = glm::rotate(transformationMatrix, (float)glfwGetTime(), glm::vec3(0, 0, 1));
		//transformationMatrix = glm::translate(transformationMatrix, glm::vec3(sin(glfwGetTime()),sin(glfwGetTime()), 0));
		
		glUniformMatrix4fv(glGetUniformLocation(program, "transform"), 1, GL_FALSE, glm::value_ptr(transformationMatrix));
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		transformationMatrix = glm::mat4(1.0f);
		double time = sin(glfwGetTime());
		if (time < 0) { time = -time; }
		transformationMatrix = glm::scale(transformationMatrix, glm::vec3(time, time, time));
		transformationMatrix = glm::translate(transformationMatrix, glm::vec3(-0.5, 0.5, 0));
		glUniformMatrix4fv(glGetUniformLocation(program, "transform"), 1, GL_FALSE, glm::value_ptr(transformationMatrix));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

    return 0;


	

}
