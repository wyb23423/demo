#include "texture.h";

void Texture::setFilename(const char* filename) {
	if (filename == src) {
		return;
	}

	deleteImageCache(src.c_str());
	src = filename;
}

Texture::Texture(const char* filename) {
	glGenTextures(1, &ID);
	setFilename(filename);
}

bool Texture::use(unsigned int format) {
	ImageData* imageData = _use();
	if (imageData) {
		glTexImage2D(TARGET, 0, format, imageData->width, imageData->height, 0, format, GL_UNSIGNED_BYTE, imageData->data);
		glGenerateMipmap(TARGET);

		return true;
	}

	return false;
}

bool Texture::use(unsigned int format, int level) {
	ImageData* imageData = _use();
	if (imageData) {
		glTexImage2D(TARGET, level, format, imageData->width, imageData->height, 0, format, GL_UNSIGNED_BYTE, imageData->data);
		return true;
	}

	return false;
}

void Texture::bind() {
	Texture::active(unit);
	glBindTexture(TARGET, ID);
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

	imageData->count++; // 增加使用计数
	return imageData;
}