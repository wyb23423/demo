#include "texture.h";
#include <glad/glad.h>;

void Texture::setFilename(const char* filename) {

}

Texture::Texture() {
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
}
Texture::Texture(const char* filename) {
	Texture();
	setFilename(filename);
}