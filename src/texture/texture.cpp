#include "texture.h"

Texture* Texture::setFilename(const char* filename) {
	if (filename == src) {
		return this;
	}

	if (isLoaded) {
		deleteImageCache(src.c_str());
		isLoaded = false;
	}

	src = filename;

	return this;
}

Texture::Texture(const char* filename) {
	glGenTextures(1, &ID);
	setFilename(filename);
}

Texture::~Texture() {
	deleteImageCache(src.c_str());
	glDeleteTextures(1, &ID);
}

bool Texture::use() {
	ImageData* imageData = _use();
	if (imageData) {
		glTexImage2D(
			TARGET, 0, imageData->format, imageData->width, imageData->height, 
			0, imageData->format, GL_UNSIGNED_BYTE, imageData->data
		);
		glGenerateMipmap(TARGET);

		return true;
	}

	return false;
}

bool Texture::use(const int level) {
	ImageData* imageData = _use();
	if (imageData) {
		glTexImage2D(
			TARGET, level, imageData->format, imageData->width, imageData->height, 
			0, imageData->format, GL_UNSIGNED_BYTE, imageData->data
		);
		return true;
	}

	return false;
}

void Texture::bind() {
	Texture::active(unit);
	glBindTexture(TARGET, ID);
}

Texture* Texture::clone() {
	Texture* texture = new Texture(src.c_str());
	texture->wraps = wraps;
	texture->wrapt = wrapt;
	texture->minFilter = minFilter;
	texture->magFilter = magFilter;
	texture->unit = unit;
	memcpy(&texture->borderColor, &borderColor, sizeof(float) * 4);

	return texture;
}

ImageData* Texture::_use() {
	ImageData* imageData = loadImage(src.c_str());
	if (!imageData) {
		return NULL;
	}

	bind();

	glTexParameteri(TARGET, GL_TEXTURE_WRAP_S, wraps);
	glTexParameteri(TARGET, GL_TEXTURE_WRAP_T, wrapt);
	glTexParameteri(TARGET, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(TARGET, GL_TEXTURE_MAG_FILTER, magFilter);

	if (wraps == GL_CLAMP_TO_BORDER || wrapt == GL_CLAMP_TO_BORDER) {
		glTexParameterfv(TARGET, GL_TEXTURE_BORDER_COLOR, borderColor);
	}

	if (!isLoaded) {
		imageData->count++; // 增加使用计数
		isLoaded = true;
	}

	return imageData;
}
