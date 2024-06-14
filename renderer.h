#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "Player.h"
#include <vector>



class renderer
{
public:
	renderer(const char* vertex, const char* fragment, const char* filepath, bool alpha);
	renderer(const char* vertex, const char* fragment);
	~renderer();
	void DrawSprite(Player player, camera Camera, glm::vec3 position, glm::vec3 size, float rotate, glm::vec3 color, float SCR_WIDTH, float SCR_HEIGHT);
	
	
private:
	camera m_Camera;
	shader Shader;
	texture* Texture;
	unsigned int quadVAO;
	bool noTexture;
	void initRenderData();
};
#endif RENDERER_H