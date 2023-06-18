//
// Created by 远坂凛的男朋友 on 2023/6/12.
//

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<iostream>
#include"shaders.h"
#include"std_image.h"
#include "Util.h"



static double x = 400.0f,y=400.0f,speed = 0.1f;
static bool in = false;
static double yaw=-90.0f,pitch = 0.0f;
static glm::vec3 direction(0.0f,0.0f,0.0f);

static void process_input(GLFWwindow* window,glm::vec3& cam_pos,const glm::vec3& look_at,const glm::vec3& cam_up,float speed = 0.03f){

    if (glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS){
        cam_pos+=speed*look_at;
    }
    else if (glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS){
        cam_pos-=speed*look_at;
    }
    else if (glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS){
        glm::vec3 right = glm::cross(look_at,cam_up);
        cam_pos-=speed*right;
    }
    else if (glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS){
        glm::vec3 right = glm::cross(look_at,cam_up);
        cam_pos+=speed*right;
    }

}

static void rotate_mouse(GLFWwindow* glfWwindow,double xpos,double ypos){

    if (!in){
        x = xpos;
        y = ypos;
        in = true;
        return;
    }


    float xMove = (xpos-x)*speed,yMove = (y - ypos)*speed;
    x = xpos;
    y = ypos;

    yaw+=xMove;
    pitch+=yMove;

    if(pitch > 89.0f){
        pitch =  89.0f;}
    if(pitch < -89.0f){
        pitch = -89.0f;}


    direction.x = cos(glm::radians(pitch))* cos(glm::radians(yaw));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw))* cos(glm::radians(pitch));

}


//static void rotate(GLFWwindow* window,glm::vec3& direction,float& pitch,float& yaw,float speed = 0.03f) {
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//        pitch = pitch+speed>89.0f?89.0f:pitch+speed;
//        direction.y = sin(glm::radians(pitch));
//    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//        pitch = pitch-speed>-89.0f?pitch-speed:-89.0f;
//        direction.y = sin(glm::radians(pitch));
//    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//        yaw-=speed;
//        direction.x = cos(glm::radians(yaw))* cos(glm::radians(pitch));
//    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//        yaw+=speed;
//        direction.x = cos(glm::radians(yaw))* cos(glm::radians(pitch));
//    }
//
//
//}


void rotate_camera(){

    GLFWwindow* glfW_window;
    init_window(&glfW_window,800,800,"smile_tube");
    unsigned int shader_program_id = glCreateProgram();
    Shader vs = Shader(threeDVertexShader,GL_VERTEX_SHADER);
    Shader fs = Shader(fragmentShaderSource6,GL_FRAGMENT_SHADER);
    fs.attach(shader_program_id);
    vs.attach(shader_program_id);
    glLinkProgram(shader_program_id);
    fs.deleteShader();
    vs.deleteShader();

    stbi_set_flip_vertically_on_load(true);

    int x,y,nrChannels;
    unsigned char* smile = stbi_load(faceSrc,&x,&y,&nrChannels,0);
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, smile);
    stbi_image_free(smile);

    unsigned int vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glUseProgram(shader_program_id);
    glEnable(GL_DEPTH_TEST);

    glm::vec3 pos(0.0f,0.0f,3.0f),front(0.0f,0.0f,0.0f),up(0.0f,1.0f,0.0f);
    float pitch = 0,yaw=0;
    glfwSetCursorPosCallback(glfW_window,rotate_mouse);

    while(!glfwWindowShouldClose(glfW_window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        process_input(glfW_window,pos,direction,up,0.01f);

        glm::mat4 project(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 model(1.0f);
        float radius = 5.0f;
        project = glm::perspective(glm::radians(45.0f),1.0f,0.1f,80.0f);
//      view = glm::lookAt(glm::vec3(radius*sin(glfwGetTime()),0.3f,radius* cos(glfwGetTime())),glm::vec3(0.3f,-1.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
        view = glm::lookAt(pos,direction+pos,up);
        for(int i=0;i<10;i++){
            glUniformMatrix4fv(glGetUniformLocation(shader_program_id,"transform"),1,GL_FALSE,glm::value_ptr(project*view*(glm::translate(model,cubePositions[i]))));
            glDrawArrays(GL_TRIANGLES,0,36);
        }
        glfwSwapBuffers(glfW_window);
        glfwPollEvents();
    }
    glfwTerminate();

}

void camera(){

    GLFWwindow* glfW_window;
    init_window(&glfW_window,800,800,"smile_tube");
    unsigned int shader_program_id = glCreateProgram();
    Shader vs = Shader(threeDVertexShader,GL_VERTEX_SHADER);
    Shader fs = Shader(fragmentShaderSource6,GL_FRAGMENT_SHADER);
    fs.attach(shader_program_id);
    vs.attach(shader_program_id);
    glLinkProgram(shader_program_id);
    fs.deleteShader();
    vs.deleteShader();

    stbi_set_flip_vertically_on_load(true);

    int x,y,nrChannels;
    unsigned char* smile = stbi_load(faceSrc,&x,&y,&nrChannels,0);
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, smile);
    stbi_image_free(smile);

    unsigned int vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glUseProgram(shader_program_id);
    glEnable(GL_DEPTH_TEST);

    glm::vec3 pos(0.0f,0.0f,0.0f),front(0.3f,1.0f,0.0f),up(0.0f,1.0f,0.0f);

    while(!glfwWindowShouldClose(glfW_window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        process_input(glfW_window,pos,front,up,0.01f);
        glm::mat4 project(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 model(1.0f);
        float radius = 5.0f;
        project = glm::perspective(glm::radians(45.0f),1.0f,0.1f,80.0f);
//        view = view = glm::lookAt(glm::vec3(radius*sin(glfwGetTime()),0.3f,radius* cos(glfwGetTime())),glm::vec3(0.3f,-1.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
        view = glm::lookAt(pos,pos+front,up);
        for(int i=0;i<10;i++){
            glUniformMatrix4fv(glGetUniformLocation(shader_program_id,"transform"),1,GL_FALSE,glm::value_ptr(project*view*glm::translate(model,cubePositions[i])));
            glDrawArrays(GL_TRIANGLES,0,36);
        }
        glfwSwapBuffers(glfW_window);
        glfwPollEvents();
    }
    glfwTerminate();
}