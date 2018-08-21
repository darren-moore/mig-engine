#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>

// The Render Engine's job is to push pixels onto the buffer.
class RenderEngine {
public:
	RenderEngine() {}
	~RenderEngine() {}

	void init();
	void stop();

	void drawRectangle(float x1, float y1, float x2, float y2);

	void setShader(Shader shader);

	void clear();
	void setClearColor(float r, float g, float b, float a);
private:
	int targetWidth_;
	int targetHeight_;
};