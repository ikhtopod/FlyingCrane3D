#pragma once

enum class TextureComponent : int {
	NONE,			///< 0: default
	GREY,			///< 1: grey
	GREY_ALPHA,		///< 2: grey, alpha
	RGB,			///< 3: red, green, blue
	RGBA			///< 4: red, green, blue, alpha
};

class Texture final {
private:
	static const GLsizei BUFFER_SIZE;

public:
	static const std::string DEFAULT_IMAGE_PATH;

private:
	GLuint id;

	std::string pathToImage;

	int width = 0;
	int height = 0;
	int nrChannels = 0; // кол-во цветовых каналов

	bool flipVertical = false; // отобразить изображение по вертикали

	TextureComponent componentsPerPixel = TextureComponent::RGBA;

private:
	void loadImage();

public:
	Texture();
	Texture(std::string _pathToImage);
	Texture(std::string _pathToImage, bool _flipVertical);
	Texture(std::string _pathToImage, bool _flipVertical,
			TextureComponent _componentsPerPixel);
	~Texture() = default;

	GLuint& getId();
	std::string getPathToImage();
	int getWidth();
	int getHeight();
};
