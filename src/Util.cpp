//
// Created by 远坂凛的男朋友 on 2023/6/12.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Util.h"
#include "std_image.h"


bool init_window(GLFWwindow** glfWwindow,int width,int height,const char* name){
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



unsigned char* load_texture(const char* file_path,const bool flip,int* width, int* height,int* nr_channels,int desired_channels){

    stbi_set_flip_vertically_on_load(flip);
    unsigned char* data = stbi_load(file_path,width,height,nr_channels,desired_channels);
    return data;

}


