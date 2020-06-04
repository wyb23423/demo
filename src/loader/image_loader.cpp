#include "stb_image.h"
#include "loader.h"
#include <iostream>

#include <glad/glad.h>

static map<const char*, ImageData*> TEXTDATA_CACHE;

ImageData* loadImage(const char* filename) {
	if (TEXTDATA_CACHE.count(filename)) {
		return TEXTDATA_CACHE.at(filename);
	}

	// 超过设置的最大缓存量, 先清空数据
	if (TEXTDATA_CACHE.size() >= CACHE_MAX_SIZE) {
		clearImageCahe();
	}

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, STBI_default);

	if (data) {
		ImageData* imageData = (ImageData*)malloc(sizeof(ImageData));
		imageData->width = width;
		imageData->height = height;
		imageData->data = data;
		imageData->count = 1;
		
		switch (nrChannels) {
		case STBI_grey:
		case STBI_grey_alpha:
			imageData->format = GL_RED;
			break;
		case STBI_rgb:
			imageData->format = GL_RGB;
			break;
		case STBI_rgb_alpha:
			imageData->format = GL_RGBA;
			break;
		default:
			imageData->format = GL_RGB;
			break;
		}

		return TEXTDATA_CACHE[filename] = imageData;
	}
	else {
		cout << "Failed to load image: " << filename << endl;
	}
	

	return NULL;
}

bool deleteImageCache(const char* filename) {
	if (!TEXTDATA_CACHE.count(filename)) {
		return false;
	}

	ImageData* imageData = TEXTDATA_CACHE.at(filename);
	imageData->count--; // 使用计数减1

	if (imageData->count <= 0) { // 不再使用, 清除内存
		stbi_image_free(imageData->data);
		free(imageData);

		TEXTDATA_CACHE.erase(filename);
	}

	return true;
}

void clearImageCahe() {
	if (TEXTDATA_CACHE.size() < 1) {
		return;
	}

	map<const char*, ImageData*>::iterator iter;
	for (iter = TEXTDATA_CACHE.begin(); iter != TEXTDATA_CACHE.end(); iter++) {
		stbi_image_free(iter->second->data);
		free(iter->second);
	}

	TEXTDATA_CACHE.clear();
}
