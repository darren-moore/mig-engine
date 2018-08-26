#pragma once

#include "Renderer.h"
#include "IOEngine.h"

class SpriteRenderer : public Renderer {
public:
	SpriteRenderer();
	SpriteRenderer(Shader* shader);
	~SpriteRenderer() {};

	void setTexture(Texture* texture);
	void draw(const Eigen::Vector2f& position, const Eigen::Vector2f& size = Eigen::Vector2f(1, 1), float rotation = 0.0f);

private:
	Texture* texture_;
	IOEngine* ioEngine_;
	GLuint VAO_;
	void initRenderData();
};