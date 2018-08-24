#pragma once

#include "Component.h"
#include "RenderEngine.h"

class Renderer : public Component {
public:
	Renderer();
	Renderer(Shader* shader);
	virtual ~Renderer() {};

protected:
	RenderEngine* renderEngine_;
	//GLuint VAO_;
	Shader* shader_;
};