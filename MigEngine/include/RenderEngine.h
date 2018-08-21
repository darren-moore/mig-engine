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

	void setShader(Shader shader);

	void clear();
	void setClearColor(float r, float g, float b, float a);
private:
	int targetWidth_;
	int targetHeight_;
};