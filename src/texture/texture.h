#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

using namespace std;

// =====================================loader
typedef struct _ImageData
{
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
	void setFilename(const char* filename);

	Texture();
	Texture(const char* filename);

private:
	unsigned int ID = 0;
	string src = "";
};

#endif