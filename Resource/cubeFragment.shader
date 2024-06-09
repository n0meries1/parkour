#version 410 core

in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 color;
uniform sampler2D image;

void main()
{
	FragColor = vec4(color, 1.0) * texture(image, TexCoord);
}