#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <assimp/material.h>
#include <glad/glad.h>

#include "../loader/loader.h"

class Texture {
public:
	// 激活纹理单元
	static void active(unsigned int unit) {
		if (unit >= GL_TEXTURE0 && unit <= GL_TEXTURE31) {
			glActiveTexture(unit);
		} else if (unit >= 0 && unit <= 31) {
			glActiveTexture(GL_TEXTURE0 + unit);
		}
	}

	// 纹理单元
	unsigned int unit = 0;
	aiTextureType type = aiTextureType_NONE; //  纹理类型

	// 纹理环绕方式
	int wraps = GL_REPEAT;
	int wrapt = GL_REPEAT;
	float borderColor[4] = { 0.0f }; // 边缘颜色。适用于环绕是GL_CLAMP_TO_BORDER时

	// 纹理过滤
	int minFilter = GL_LINEAR_MIPMAP_LINEAR;
	int magFilter = GL_LINEAR;

	Texture* setFilename(const char* filename);

	Texture(const char* filename = "");
	~Texture();

	// 加载并使用纹理配置
	bool use(); // 自动设置多级渐远纹理的级别
	bool use(const int level); //  手动设置多级渐远纹理的级别

	// 绑定纹理
	void bind();
	// 克隆当前纹理
	Texture* clone();

protected:
	// 纹理目标
	const int TARGET = GL_TEXTURE_2D;

	unsigned int ID = 0;
	string src = "";

	// 是否加载过纹理数据
	bool isLoaded = false;

	// 加载并配置纹理
	ImageData* _use();
};

#endif