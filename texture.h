#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb/stb_image.h>
#endif

class texture
{
public:
	unsigned int ID;
	texture(const char* filepath, bool alpha);
	void Bind() const;
	void Unbind() const;
	bool loaded;

};


#endif
