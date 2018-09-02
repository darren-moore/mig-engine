#pragma once

#include "Renderer.h"
#include "ResourceEngine.h"

class PrimitiveRenderer : public Renderer {
public:
	PrimitiveRenderer();
	PrimitiveRenderer(Shader* shader);


private:
	IOEngine* ioEngine_;

};