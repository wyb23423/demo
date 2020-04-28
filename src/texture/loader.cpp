#include "stb_image.h";
#include "texture.h";
#include <map>

static constexpr int CACHE_MAX_SIZE = 5000;

static map<const char*, ImageData*> TEXTDATA_CACHE;

ImageData* loadImage(const char* filename) {
	if (TEXTDATA_CACHE.count(filename)) {
		return TEXTDATA_CACHE.at(filename);
	}

	// 超过设置的最大缓存量, 先清空数据
	if (TEXTDATA_CACHE.size >= CACHE_MAX_SIZE) {
		clearImageCahe();
	}

	ImageData* imageData = (ImageData*)malloc(sizeof(ImageData));
	imageData->data = stbi_load(filename, &imageData->width, &imageData->height, &imageData->nrChannels, 0);

	TEXTDATA_CACHE[filename] = imageData;

	return imageData;
}

bool deleteImageCache(const char* filename) {
	if (!TEXTDATA_CACHE.count(filename)) {
		return false;
	}

	ImageData* imageData = TEXTDATA_CACHE.at(filename);
	stbi_image_free(imageData->data);
	free(imageData);

	TEXTDATA_CACHE.erase(filename);

	return true;
}

void clearImageCahe() {
	if (TEXTDATA_CACHE.size < 1) {
		return;
	}

	map<const char*, ImageData*>::iterator iter;
	for (iter = TEXTDATA_CACHE.begin(); iter != TEXTDATA_CACHE.end(); iter++) {
		stbi_image_free(iter->second->data);
		free(iter->second);
	}

	TEXTDATA_CACHE.clear();
}
