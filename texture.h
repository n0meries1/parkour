#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

class texture
{
public:
	unsigned int ID;
	texture(const char* filepath, bool alpha);
	void Bind() const;
	void Unbind() const;
private:

};


#endif
