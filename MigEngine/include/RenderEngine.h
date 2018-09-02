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
	void drawLine(float x1, float y1, float x2, float y2);
	void drawRectangle(float x1, float y1, float x2, float y2);
	void drawCircle(float x, float y, float r);
	void setCircleNumSides(int n);

	void clear();
	void setClearColor(float r, float g, float b, float a);
private:
	void initTextureData();
	GLuint textureVAO_;
	Shader* textureShader_;
	IOEngine* ioEngine_;
	int targetWidth_;
	int targetHeight_;

	Shader* primitiveShader_;
	GLuint rectangleVAO_;
	GLuint circleVAO_;
	GLuint lineVAO_;
	void initCircleData(int nSides);
	void initRectangleData();
	void initLineData();
	int circleNumSides_ = 32;

};