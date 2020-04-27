#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "include/util.h"
#include <iostream>

GLuint createShader(GLenum type, const char*source) {
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
