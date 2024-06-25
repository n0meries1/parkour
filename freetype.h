#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <map>
#include <string>
#include <glm/glm/glm.hpp>
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Shader.h"

struct Character
{
	unsigned int characterID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class TextRenderer
{
public:
	TextRenderer(float width, float height);
	void LoadFont(const std::string& fontpath, float fontsize);
	void RenderText(const std::string& text, float x, float y, float scale, glm::vec3 color);
private:
	std::map <float, Character> Characters;
	shader TextShader;
	unsigned int VAO, VBO;
	float Width, Height;


};
#endif