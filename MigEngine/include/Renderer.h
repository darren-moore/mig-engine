#pragma once

#include "GameObjectComponent.h"
#include "Shader.h"

class Renderer : public GameObjectComponent{
public:
	Renderer(Shader &shader) : shader_(shader) {};
	~Renderer() {};

protected:
	GLuint VAO_;
	Shader shader_;

};