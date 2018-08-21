#pragma once

#include "Renderer.h"
#include "IOEngine.h"

class SpriteRenderer : public Renderer {
public:
	SpriteRenderer();
	SpriteRenderer(Shader* shader);
	~SpriteRenderer() {};

	void draw(glm::vec2 position, glm::vec2 size = glm::vec2(1, 1), GLfloat rotation = 0.0f);

private:
	IOEngine* ioEngine_;
	void initRenderData();
};