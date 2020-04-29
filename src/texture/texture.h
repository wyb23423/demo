#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad\glad.h>

using namespace std;

// =====================================loader
typedef struct _ImageData
{
	int count; // 使用次数
	int width;
	int height;
	int nrChannels;
	unsigned char* data;
} ImageData;

// 加载图片数据。如果已存在直接返回缓存数据
ImageData* loadImage(const char* filename);
// 根据键名删除图片缓存数据
bool deleteImageCache(const char* filename);
// 清空图片缓存数据
void clearImageCahe();

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

	// 纹理环绕方式
	int wraps = GL_REPEAT;
	int wrapt = GL_REPEAT;
	float borderColor[4] = { 0.0f }; // 边缘颜色。适用于环绕是GL_CLAMP_TO_BORDER时

	// 纹理过滤
	int minFilter = GL_NEAREST;
	int magFilter = GL_NEAREST;

	void setFilename(const char* filename);

	Texture();
	Texture(const char* filename);

	// 加载并使用纹理配置
	// format 数据类型如： GL_RGB/GL_RGBA
	bool use(unsigned int format); // 自动生成所有需要的多级渐远纹理
	bool use(unsigned int format, int level); // 手动设置多级渐远纹理的级别

	// 绑定纹理
	void bind();

protected:
	// 纹理目标
	const int TARGET = GL_TEXTURE_2D;

	unsigned int ID = 0;
	string src = "";

	// 加载并配置纹理
	ImageData* _use();
};

#endif