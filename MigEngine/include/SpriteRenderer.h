#pragma once

#include "Renderer.h"
#include "IOEngine.h"

class SpriteRenderer : Renderer {
public:
	SpriteRenderer(Shader &shader);		// Want to use a default shader if none is specified.

	void draw(glm::vec2 position, glm::vec2 size = glm::vec2(1, 1), GLfloat rotation = 0.0f);

private:
	Shader shader_;
	IOEngine ioEngine_;
	void initRenderData();
};