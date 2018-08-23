#pragma once

#include "Renderer.h";
#include "ResourceEngine.h"

class PrimitiveRenderer : public Renderer {
public:
	PrimitiveRenderer();
	PrimitiveRenderer(Shader* shader);
	void initRenderData();
	void drawRectangle(float x1, float y1, float x2, float y2);
private:
	IOEngine* ioEngine_;

};