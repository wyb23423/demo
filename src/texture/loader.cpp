#include "stb_image.h"
#include "texture.h"
#include <map>
#include <iostream>

static constexpr int CACHE_MAX_SIZE = 5000; // ��󻺴���

static map<const char*, ImageData*> TEXTDATA_CACHE;

ImageData* loadImage(const char* filename) {
	if (TEXTDATA_CACHE.count(filename)) {
		return TEXTDATA_CACHE.at(filename);
	}

	// �������õ���󻺴���, ���������
	if (TEXTDATA_CACHE.size() >= CACHE_MAX_SIZE) {
		clearImageCahe();
	}

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

	if (data) {
		ImageData* imageData = (ImageData*)malloc(sizeof(ImageData));
		imageData->width = width;
		imageData->height = height;
		imageData->nrChannels = nrChannels;
		imageData->data = data;
		imageData->count = 0;

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
	imageData->count--; // ʹ�ü�����1

	if (imageData->count <= 0) { // ����ʹ��, ����ڴ�
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