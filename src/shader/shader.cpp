#include "shader.h"
#include <glm/gtc/type_ptr.hpp>

std::string Shader::getVertexCode() {
    return vertexCode;
}
Shader* const Shader::setVertexCode(const GLchar* path) {
    loadCode(path, SHARDER_TYPE::VERTEX);
    return this;
}
Shader* const Shader::setVertexCode(const std::string &source) {
    vertexCode = source;
    return this;
}

std::string Shader::getFragmentCode() {
    return fragmentCode;
}
Shader* const Shader::setFragmentCode(const GLchar* path) {
    loadCode(path, SHARDER_TYPE::FRAGMENT);
    return this;
}
Shader* const Shader::setFragmentCode(const std::string &source) {
    fragmentCode = source;
    return this;
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

bool Shader::compile() {
    GLuint vertextShader = compileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

    if (!vertextShader || !fragmentShader) {
        return 0;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertextShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    int success = 1;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;

        return 0;
    }

    glDeleteShader(vertextShader);
    glDeleteShader(fragmentShader);

    return 1;
}

// 使用/激活程序
Shader* const Shader::use() {
    glUseProgram(ID);
    return this;
}
// uniform工具函数
Shader* const Shader::setUniform(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    return this;
}
Shader* const Shader::setUniform(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    return this;
}
Shader* const Shader::setUniform(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    return this;
}
Shader* const Shader::setUniform(const std::string& name, float x, float y) {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    return this;
};
Shader* const Shader::setUniform(const std::string& name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    return this;
};
Shader* const Shader::setUniform(const std::string& name, glm::vec2& value) {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
    return this;
};
Shader* const Shader::setUniform(const std::string& name, glm::vec3& value) {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
    return this;
};
Shader* const Shader::setUniform(const std::string& name, glm::mat3& transform) {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(transform));
    return this;
}
Shader* const Shader::setUniform(const std::string& name, glm::mat4& transform) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(transform));
    return this;
}

GLuint Shader::compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success = 1;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;

        return 0;
    }

    return shader;
}

void Shader::loadCode(const GLchar* path, SHARDER_TYPE type) {
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // 打开文件
        shaderFile.open(path);
        std::stringstream shaderStream;
        // 读取文件的缓冲内容到数据流中
        shaderStream << shaderFile.rdbuf();
        // 关闭文件处理器
        shaderFile.close();
        // 转换数据流到string
        switch (type) {
        case SHARDER_TYPE::VERTEX:
                vertexCode = shaderStream.str();
                break;
        case SHARDER_TYPE::FRAGMENT:
                fragmentCode = shaderStream.str();
                break;
            default: break;
        }
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}
