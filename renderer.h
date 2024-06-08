#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"

class renderer
{
public:
	renderer(const char* vertexShader, const char* fragmentShader, const char* texture = nullptr);
private:
};
#endif RENDERER_H