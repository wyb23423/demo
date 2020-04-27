#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


// 创建着色器程序
// @return 创建的着色器程序ID, 0表示失败
GLuint createProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

// 绑定顶点数据
// @param VAO 顶点数组对象
// @param VBO 顶点缓冲对象
void bindVertices(float vertices[], GLsizeiptr size, GLuint* VAO, GLuint* VBO);
