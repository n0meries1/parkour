#include "texture.h"

texture::texture(const char* filepath, bool alpha)
{
	if (filepath == nullptr)
	{
		std::cerr << "ERROR::TEXTURE: No filepath provided" << std::endl;
		loaded = false;
		return;
	}

	int width, height, nrChannels;
	unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cerr << "ERROR::TEXTURE: Failed to load texture file" << filepath << std::endl; 
		throw std::runtime_error("Failed to laod texture");
	}

	stbi_image_free(data);

	glGenTextures(1, &this->ID);
	glBindTexture(GL_TEXTURE_2D, this->ID);

	if (alpha)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	loaded = true;
}


void texture::Bind() const
{
	if (loaded)
	{
		glBindTexture(GL_TEXTURE_2D, this->ID);
	}
	else
	{
		std::cerr << "ERROR::TEXTURE: Attempted to bind an unloaded texture" << std::endl;
	}
}

void texture::Unbind() const
{
	if (loaded)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}