#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// 动态编译着色器
// @param type 着色器类型, 通常是GL_VERTEX_SHADER或GL_FRAGMENT_SHADER
// @param source
// @return 创建的着色器ID, 0表示编译失败
unsigned int createShader(GLenum type, const char* source);

// 创建着色器程序
// @return 创建的着色器程序ID, 0表示失败
GLuint createProgram(GLuint vertextShader, GLuint fragmentShader);

