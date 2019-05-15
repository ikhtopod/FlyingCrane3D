#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include <stb_image.h>


const GLsizei Texture::BUFFER_SIZE = 1;

const std::string Texture::DEFAULT_IMAGE_PATH =
R"(..\resources\icons\multimedia-icons\png\cancel-1.png)";


Texture::Texture() : Texture(Texture::DEFAULT_IMAGE_PATH) {}

Texture::Texture(std::string _pathToImage) :
	Texture(_pathToImage, false) {}

Texture::Texture(std::string _pathToImage, bool _flipVertical) :
	Texture(_pathToImage, _flipVertical, TextureComponent::RGBA) {}

Texture::Texture(std::string _pathToImage, bool _flipVertical,
				 TextureComponent _componentsPerPixel) :
	pathToImage(_pathToImage), flipVertical(_flipVertical),
	componentsPerPixel(_componentsPerPixel) {

	this->loadImage();
}


void Texture::loadImage() {
	stbi_set_flip_vertically_on_load(this->flipVertical);

	UINT8* data = stbi_load(this->pathToImage.c_str(),
							&this->width, &this->height, &this->nrChannels,
							static_cast<int>(this->componentsPerPixel));

	glGenTextures(Texture::BUFFER_SIZE, &this->id);
	glBindTexture(GL_TEXTURE_2D, this->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D,
					 0, GL_RGBA, this->width, this->height,
					 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}//fi

	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint& Texture::getId() { return this->id; }
std::string Texture::getPathToImage() { return this->pathToImage; }
int Texture::getWidth() { return this->width; }
int Texture::getHeight() { return this->height; }
