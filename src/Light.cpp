//
// Created by 远坂凛的男朋友 on 2023/6/14.
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
#include "Camera.h"


static bool in = false;
static Camera* camera1;
static float x,y;







static void mouse_call_back(GLFWwindow* glfW_window,double xpos,double ypos){
    if (!in){
        x = camera1->Front.x;
        y = camera1->Front.y;
        in = true;
        return;
    }

    float x_offset = xpos-x,y_offset = y-ypos;
    x = xpos;
    if (x==0){
        x = 1000;
    }
    y = ypos;
    camera1->ProcessMouseMovement(x_offset,y_offset);
}


void keyboard_event(GLFWwindow* window){

    if (glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS){
        camera1->ProcessKeyboard(FORWARD,1.0f);
    }
    else if (glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS){
        camera1->ProcessKeyboard(BACKWARD,1.0f);
    }
    else if (glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS){
        camera1->ProcessKeyboard(LEFT,1.0f);
    }
    else if (glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS){
        camera1->ProcessKeyboard(RIGHT,1.0f);
    }

}



void light_texture(){



    GLFWwindow* glfW_window;
    if (!init_window(&glfW_window,1000,1000)){
        std::cout<<"Error"<<std::endl;
        return;
    }

    ShaderPlus light("Shaders/NormalVertexShader.glsl","Shaders/NormalFragmentShader.glsl"),object("Shaders/LightTextureVertexShader.glsl","Shaders/LightTextureFragmentShader.glsl");
    float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    unsigned int vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture_box;
    glGenTextures(1,&texture_box);
    glBindTexture(GL_SAMPLER_2D,texture_box);
    int width,height,nr_channels;
    unsigned char* box_pic = load_texture("container.jpg", true,&width,&height,&nr_channels,0);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,box_pic);
    stbi_image_free(box_pic);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


    glm::mat4 basic(1.0f);
    glm::vec3 object_location(1.0f,1.0f,-1.5f);
    glm::vec3 cam_pos(1.5f,1.0f,1.3f);
    Camera camera(cam_pos,glm::vec3(3.0f,0.0f,-2.5f),glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 view = glm::lookAt(cam_pos,cam_pos+glm::vec3(-0.5f,-0.5f,-0.8f),glm::vec3(0.0f,1.0f,0.0f));
    camera1 = &camera;
    glm::mat4 object_model = glm::translate(glm::scale(glm::rotate(basic, (float)abs(sin(glfwGetTime()))*90.0f,glm::vec3(1.0f,0.0f,0.0f)),glm::vec3(0.5f,0.5f,0.5f)),object_location);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f),1.0f,0.1f,150.0f);
    glm::vec3 ob_color(1.0f, 0.5f, 0.421f);
    glm::vec3 light_c(1.0f,1.0f,1.0f);
    glm::vec3 ami(0.2f,0.1f,0.1f);
    glfwSetCursorPosCallback(glfW_window,mouse_call_back);
    glEnable(GL_DEPTH_TEST);
    float radius = 5.0f;
    glm::vec3 lighter_location(1.0f);
    while(!glfwWindowShouldClose(glfW_window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        keyboard_event(glfW_window);
        object_model = glm::scale(glm::rotate(glm::translate(basic,object_location),(float)glfwGetTime(),glm::vec3(1.0f,0.0f,1.0f)),glm::vec3(0.5f));
        light.use();

        glm::mat4 lighter_model = glm::scale(glm::translate(basic,lighter_location),glm::vec3(0.5f));

        light.setMat4("trans",projection*camera.GetViewMatrix()*lighter_model);
        glDrawArrays(GL_TRIANGLES,0,36);

        light_c = glm::vec3(sin(glm::radians(abs(glfwGetTime()))));

        object.use();
        object.setMat4("trans",projection*camera.GetViewMatrix()*object_model);
        object.setMat4("model_view",camera.GetViewMatrix()*object_model);
        object.setMat4("trans_normal",glm::transpose(glm::inverse(camera.GetViewMatrix()*object_model)));
        //object.setVec3("light_model_pos",lighter_location);
        object.setVec3("light.pos",camera.GetViewMatrix()*glm::vec4(camera.Position,1.0f));
        object.setVec3("light.ambient",glm::vec3(1.0f));
        object.setVec3("light.diffuse",glm::vec3(1.0f));
        object.setVec3("light.specular",glm::vec3(1.0f));
        object.setInt("material.tex",0);
        object.setFloat("material.shiness",32);
        object.setVec3("material.specular",glm::vec3(0.05f));
        glDrawArrays(GL_TRIANGLES,0,36);


        glm::mat4 object_model_copy = glm::scale(glm::rotate(glm::translate(basic,object_location+glm::vec3(glm::sin(glfwGetTime()))),(float)glfwGetTime(),glm::vec3(1.0f,0.0f,1.0f)),glm::vec3(0.5f));
        object.setMat4("model",object_model_copy);
        object.setMat4("trans",projection*camera.GetViewMatrix()*object_model_copy);
        glDrawArrays(GL_TRIANGLES,0,36);







        glfwSwapBuffers(glfW_window);
        glfwPollEvents();

    }
    glfwTerminate();


}


void material_light(){

    GLFWwindow* glfW_window;
    if (!init_window(&glfW_window,1000,1000)){
        std::cout<<"Error"<<std::endl;
        return;
    }

    ShaderPlus light("Shaders/NormalVertexShader.glsl","Shaders/NormalFragmentShader.glsl"),object("Shaders/DiffuseLightVertexShader.glsl","Shaders/DiffuseLightFragmentShader.glsl");
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    unsigned int vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glm::mat4 basic(1.0f);
    glm::vec3 object_location(1.0f,1.0f,-1.5f);
    glm::vec3 cam_pos(1.5f,1.0f,1.3f);
    Camera camera(cam_pos,glm::vec3(3.0f,0.0f,-2.5f),glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 view = glm::lookAt(cam_pos,cam_pos+glm::vec3(-0.5f,-0.5f,-0.8f),glm::vec3(0.0f,1.0f,0.0f));
    camera1 = &camera;
    glm::mat4 object_model = glm::translate(glm::scale(glm::rotate(basic, (float)abs(sin(glfwGetTime()))*90.0f,glm::vec3(1.0f,0.0f,0.0f)),glm::vec3(0.5f,0.5f,0.5f)),object_location);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f),1.0f,0.1f,150.0f);
    glm::vec3 ob_color(1.0f, 0.5f, 0.421f);
    glm::vec3 light_c(1.0f,1.0f,1.0f);
    glm::vec3 ami(0.2f,0.1f,0.1f);
    glfwSetCursorPosCallback(glfW_window,mouse_call_back);
    glEnable(GL_DEPTH_TEST);
    float radius = 5.0f;
    glm::vec3 lighter_location(1.0f);
    while(!glfwWindowShouldClose(glfW_window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        keyboard_event(glfW_window);
        object_model = glm::scale(glm::rotate(glm::translate(basic,object_location),(float)glfwGetTime(),glm::vec3(1.0f,0.0f,1.0f)),glm::vec3(0.5f));
        light.use();

        glm::mat4 lighter_model = glm::scale(glm::translate(basic,lighter_location),glm::vec3(0.5f));

        light.setMat4("trans",projection*camera.GetViewMatrix()*lighter_model);
        glDrawArrays(GL_TRIANGLES,0,36);

        light_c = glm::vec3(sin(glm::radians(abs(glfwGetTime()))));

        object.use();
        object.setMat4("trans",projection*camera.GetViewMatrix()*object_model);
        object.setMat4("model",object_model);
        object.setMat4("view",camera.GetViewMatrix());
        //object.setVec3("light_model_pos",lighter_location);
        object.setVec3("light.pos",camera.GetViewMatrix()*glm::vec4(camera.Position,1.0f));
        object.setVec3("light.ambient",glm::vec3(1.0f));
        object.setVec3("light.diffuse",glm::vec3(1.0f));
        object.setVec3("light.specular",glm::vec3(1.0f));
        object.setVec3("material.diffuse",glm::vec3(0.07f,0.6f,0.07f));
        object.setFloat("material.shine",0.6f*128);
        object.setVec3("material.ambient",glm::vec3(0.02f,0.1745f,0.0215f));
        object.setVec3("material.specular",glm::vec3(0.633f,0.727811f,0.633f));
        glDrawArrays(GL_TRIANGLES,0,36);


        glm::mat4 object_model_copy = glm::scale(glm::rotate(glm::translate(basic,object_location+glm::vec3(glm::sin(glfwGetTime()))),(float)glfwGetTime(),glm::vec3(1.0f,0.0f,1.0f)),glm::vec3(0.5f));
        object.setMat4("model",object_model_copy);
        object.setMat4("trans",projection*camera.GetViewMatrix()*object_model_copy);
        glDrawArrays(GL_TRIANGLES,0,36);







        glfwSwapBuffers(glfW_window);
        glfwPollEvents();

    }
    glfwTerminate();


}



void phong_light_model(){







    GLFWwindow* glfW_window;
    if (!init_window(&glfW_window,1000,1000)){
        std::cout<<"Error"<<std::endl;
        return;
    }

    ShaderPlus light("D:/opengl/src/Shaders/NormalVertexShader.glsl","D:/opengl/src/Shaders/NormalFragmentShader.glsl"),object("D:/opengl/src/Shaders/DiffuseLightVertexShader.glsl","D:/opengl/src/Shaders/DiffuseLightFragmentShader.glsl");
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    unsigned int vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glm::mat4 basic(1.0f);
    glm::vec3 object_location(1.0f,1.0f,-1.5f);
    glm::vec3 cam_pos(1.5f,1.0f,1.3f);
    Camera camera(cam_pos,glm::vec3(3.0f,0.0f,-2.5f),glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 view = glm::lookAt(cam_pos,cam_pos+glm::vec3(-0.5f,-0.5f,-0.8f),glm::vec3(0.0f,1.0f,0.0f));
    camera1 = &camera;
    glm::mat4 object_model = glm::translate(glm::scale(glm::rotate(basic, (float)abs(sin(glfwGetTime()))*90.0f,glm::vec3(1.0f,0.0f,0.0f)),glm::vec3(0.5f,0.5f,0.5f)),object_location);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f),1.0f,0.1f,150.0f);
    glm::vec3 ob_color(1.0f, 0.5f, 0.421f);
    glm::vec3 light_c(1.0f,1.0f,1.0f);
    glm::vec3 ami(0.2f,0.1f,0.1f);
    glfwSetCursorPosCallback(glfW_window,mouse_call_back);
    glEnable(GL_DEPTH_TEST);
    float radius = 5.0f;
    glm::vec3 lighter_location(1.0f);
    while(!glfwWindowShouldClose(glfW_window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        keyboard_event(glfW_window);
        object_model = glm::scale(glm::rotate(glm::translate(basic,object_location),(float)glfwGetTime(),glm::vec3(1.0f,0.0f,1.0f)),glm::vec3(0.5f));
//        light.use();
//
//        glm::mat4 lighter_model = glm::scale(glm::translate(basic,lighter_location),glm::vec3(0.5f));
//
//        light.setMat4("trans",projection*camera.GetViewMatrix()*lighter_model);
//        glDrawArrays(GL_TRIANGLES,0,36);

//        light_c = glm::vec3(sin(glm::radians(abs(glfwGetTime()))));

        object.use();
        object.setMat4("trans",projection*camera.GetViewMatrix()*object_model);
        object.setMat4("model",object_model);
        object.setMat4("view",camera.GetViewMatrix());
        //object.setVec3("light_model_pos",lighter_location);
        object.setVec3("light_pos",camera.GetViewMatrix()*glm::vec4(camera.Position,1.0f));
        object.setVec3("cam_pos",camera.Position);
        object.setVec3("object_color",ob_color);
        object.setVec3("light",light_c);
        object.setVec3("ambient",ami);
        glDrawArrays(GL_TRIANGLES,0,36);


        glm::mat4 object_model_copy = glm::scale(glm::rotate(glm::translate(basic,object_location+glm::vec3(glm::sin(glfwGetTime()))),(float)glfwGetTime(),glm::vec3(1.0f,0.0f,1.0f)),glm::vec3(0.5f));
        object.setMat4("model",object_model_copy);
        object.setMat4("trans",projection*camera.GetViewMatrix()*object_model_copy);
        glDrawArrays(GL_TRIANGLES,0,36);







        glfwSwapBuffers(glfW_window);
        glfwPollEvents();

    }
    glfwTerminate();




}

void light(){

    GLFWwindow* glfW_window;
    if(!init_window(&glfW_window)){
        std::cout<<"Error"<<std::endl;
        return;
    }

    Shader vs(transformationVertexShader,GL_VERTEX_SHADER);
    Shader light_cube_fs(light_cube_shader,GL_FRAGMENT_SHADER);
    Shader light_fs(light_shader,GL_FRAGMENT_SHADER);
    unsigned int cube_shader = glCreateProgram();
    unsigned int light_shader = glCreateProgram();
    vs.attach(cube_shader);
    vs.attach(light_shader);
    light_cube_fs.attach(cube_shader);
    light_fs.attach(light_shader);
    light_fs.deleteShader();
    light_cube_fs.deleteShader();
    glLinkProgram(cube_shader);
    glLinkProgram(light_shader);

    vs.deleteShader();
    unsigned int vbo;
    unsigned int vao_cube,vao_light;
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&vao_cube);
    glGenVertexArrays(1,&vao_cube);
    glGenVertexArrays(1,&vao_light);
    glBindVertexArray(vao_cube);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
    };

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);



    while(!glfwWindowShouldClose(glfW_window)){
        glClear(GL_COLOR_BUFFER_BIT);

        //render
        glUseProgram(light_shader);
        glm::mat4 model(1.0f);
        glm::mat4 light_model = glm::translate(model,glm::vec3(1.2f,0.0f,-3.0f));
        glm::mat4 view = glm::lookAt(glm::vec3(2.0f,3.0f,4.0f),glm::vec3(0.3f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(55.0f),1.0f,0.1f,100.0f);
        glUniformMatrix4fv(glGetUniformLocation(light_shader,"transform"),1,GL_FALSE,glm::value_ptr(projection*view*light_model));
        glDrawArrays(GL_TRIANGLES,0,36);
        glm::mat4 cube_model = glm::translate(model,glm::vec3(0.0f,0.0f,0.0f));
        glUseProgram(cube_shader);
        glUniformMatrix4fv(glGetUniformLocation(cube_shader,"transform"),1,GL_FALSE,glm::value_ptr(projection*view*cube_model));
        glUniform3fv(glGetUniformLocation(cube_shader,"object_color"),1,&(glm::vec3(0.3f,0.6f,0.5f))[0]);
        glUniform3fv(glGetUniformLocation(cube_shader,"light_color"),1,&(glm::vec3(1.0f,1.0f,1.0f))[0]);
        glDrawArrays(GL_TRIANGLES,0,36);

        glfwSwapBuffers(glfW_window);
        glfwPollEvents();

    }

    glfwTerminate();





}