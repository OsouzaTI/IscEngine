#include "Texture.hpp"
using namespace IscEngine;

void Texture::bind(const Texture* const texture, const unsigned int index) {

	glActiveTexture(index);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->id);

}

void Texture::unbind(const unsigned int index) {

	glActiveTexture(index);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

}

Texture::Texture() {

	this->id = 0;

}

Texture::~Texture() {

	glDeleteTextures(1, &this->id);

}

bool Texture::loadFromFile(const char* const fileName) {

	sf::Image image;
	if (!image.loadFromFile(fileName)) return false;

	glGenTextures(1, &this->id);

	Texture::bind(this);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	Texture::unbind();

	return true;

}

void Texture::create(const unsigned int width, const unsigned int height, const bool color, const bool depth) {

	glGenTextures(1, &this->id);
	Texture::bind(this);

	if (color) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	else if (depth) glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	// Poor filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	if (!color) {
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	Texture::unbind();

}