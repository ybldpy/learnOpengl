//
// Created by 远坂凛的男朋友 on 2023/6/12.
//
#ifndef DEMO1_UTIL_H
#define DEMO1_UTIL_H
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

bool init_window(GLFWwindow** glfWwindow,int width=800,int height=800,const char* name="Window");
unsigned char* load_texture(const char* file_path,const bool flip,int* width, int* height,int* nr_channels,int desired_channels);
#endif // DEMO1_UTIL_H
