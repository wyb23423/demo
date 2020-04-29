#include "texture.h";

void Texture::setFilename(const char* filename) {
	deleteImageCache(src.c_str());
	src = filename;
}

Texture::Texture() {
	glGenTextures(1, &ID);
	glBindTexture(TARGET, ID);
}
Texture::Texture(const char* filename) {
	Texture();
	setFilename(filename);
}

bool Texture::use() {
	ImageData* imageData = _use();
	if (imageData) {
		glTexImage2D(TARGET, 0, GL_RGB, imageData->width, imageData->height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData->data);
		glGenerateMipmap(TARGET);

		return true;
	}

	return false;
}

bool Texture::use(int level) {
	ImageData* imageData = _use();
	if (imageData) {
		glTexImage2D(TARGET, level, GL_RGB, imageData->width, imageData->height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData->data);
		return true;
	}

	return false;
}

void Texture::bind() {
	glBindTexture(TARGET, ID);
}

ImageData* Texture::_use() {
	ImageData* imageData = loadImage(src.c_str());
	if (!imageData) {
		return NULL;
	}

	glTexParameteri(TARGET, GL_TEXTURE_WRAP_S, wraps);
	glTexParameteri(TARGET, GL_TEXTURE_WRAP_T, wrapt);
	glTexParameteri(TARGET, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(TARGET, GL_TEXTURE_MAG_FILTER, magFilter);

	if (wraps == GL_CLAMP_TO_BORDER || wrapt == GL_CLAMP_TO_BORDER) {
		glTexParameterfv(TARGET, GL_TEXTURE_BORDER_COLOR, borderColor);
	}

	return imageData;
}