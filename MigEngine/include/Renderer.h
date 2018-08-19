#pragma once

#include "GameObjectComponent.h"
#include "Shader.h"

class Renderer : public GameObjectComponent{
public:
	Renderer(Shader &shader) : shader(shader) {};
	~Renderer() {};

protected:
	GLuint VAO;
	Shader shader;

};