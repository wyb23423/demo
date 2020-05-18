#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件
#include <glm/mat4x4.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

enum SHARDER_TYPE { VERTEX, FRAGMENT };

class Shader {
public:
    std::string getVertexCode();
    Shader* const setVertexCode(const GLchar* path);
    Shader* const setVertexCode(const std::string &source);

    std::string getFragmentCode();
    Shader* const setFragmentCode(const GLchar* path);
    Shader* const setFragmentCode(const std::string &source);

    // 构建着色器
    bool compile();
    // 使用/激活程序
    Shader* const use();
    // uniform工具函数
    Shader* const setUniform(const std::string &name, bool value);
    Shader* const setUniform(const std::string &name, int value);
    Shader* const setUniform(const std::string &name, float value);
    Shader* const setUniform(const std::string& name, float x, float y);
    Shader* const setUniform(const std::string& name, float x, float y, float z);
    Shader* const setUniform(const std::string& name, glm::mat4& transform);

private:
    // 程序ID
    GLuint ID = 0;
    std::string vertexCode = "";
    std::string fragmentCode = "";

    GLuint compileShader(GLenum type, const char* source);
    void loadCode(const GLchar* path, SHARDER_TYPE type);
};

#endif