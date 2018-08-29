#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <Eigen/Core>
#include "Texture.h"
#include "IOEngine.h"
#include "Shader.h"

// The Render Engine's job is to push pixels onto the buffer.
class RenderEngine {
public:
	RenderEngine() {}
	~RenderEngine() {}

	void init();
	void stop();

	void setShader(Shader shader);

	void drawTexture(Texture* texture, const Eigen::Vector2f& position, const Eigen::Vector2f& size = Eigen::Vector2f(1, 1), float rotation = 0.0f);

	void clear();
	void setClearColor(float r, float g, float b, float a);
private:
	void initTextureData();
	GLuint textureVAO_;
	Shader* textureShader_;
	IOEngine* ioEngine_;
	int targetWidth_;
	int targetHeight_;
};