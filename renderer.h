#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include "texture.h"


class renderer
{
public:
	renderer(const char* vertex, const char* fragment, const char* filepath, bool alpha);
	renderer(const char* vertex, const char* fragment);
	~renderer();
	void DrawSprite(glm::vec3 position, glm::vec3 size, float rotate, glm::vec3 color);

	
private:
	shader Shader;
	texture* Texture;
	unsigned int quadVAO;
	bool noTexture;
	void initRenderData();
};
#endif RENDERER_H