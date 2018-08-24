#pragma once

#include "Renderer.h";
#include "ResourceEngine.h"

class PrimitiveRenderer : public Renderer {
public:
	PrimitiveRenderer();
	PrimitiveRenderer(Shader* shader);
	
	void drawRectangle(float x1, float y1, float x2, float y2);
	void drawCircle(float x, float y, float r);
	void setCircleNumSides(int n);

private:
	IOEngine* ioEngine_;
	GLuint rectangleVAO_;
	GLuint circleVAO_;
	void initCircleData(int nSides);
	void initRectangleData();
	int circleNumSides_ = 32;
}; 