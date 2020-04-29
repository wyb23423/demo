#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

enum SHARDER_TYPE { VERTEX, FRAGMENT };

class Shader {
public:
    std::string getVertexCode();
    void setVertexCode(const GLchar* path);
    void setVertexCode(const std::string &source);

    std::string getFragmentCode();
    void setFragmentCode(const GLchar* path);
    void setFragmentCode(const std::string &source);

    // 构建着色器
    bool compile();
    // 使用/激活程序
    void use();
    // uniform工具函数
    void setUniform(const std::string &name, bool value);
    void setUniform(const std::string &name, int value);
    void setUniform(const std::string &name, float value);

private:
    // 程序ID
    GLuint ID = 0;
    std::string vertexCode = "";
    std::string fragmentCode = "";

    GLuint compileShader(GLenum type, const char* source);
    void loadCode(const GLchar* path, SHARDER_TYPE type);
};

#endif