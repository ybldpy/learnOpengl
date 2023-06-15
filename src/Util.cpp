//
// Created by 远坂凛的男朋友 on 2023/6/12.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>


bool init_window(GLFWwindow** glfWwindow,int width=800,int height=800,const char* name="Window"){
    if (!glfwInit()){
        return false;
    }
    *glfWwindow = glfwCreateWindow(width,height,name,NULL,NULL);
    if (!*glfWwindow){
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*glfWwindow);
    glewInit();
    return true;
}