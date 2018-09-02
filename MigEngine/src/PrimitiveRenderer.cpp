#include "PrimitiveRenderer.h"
#include <Eigen/Dense>
#include "LAutils.h"
#include "Locator.h"



using namespace Eigen;

PrimitiveRenderer::PrimitiveRenderer() : Renderer() {


	ioEngine_ = Locator::getIOEngine();
}

PrimitiveRenderer::PrimitiveRenderer(Shader* shader) : Renderer(shader) {
	PrimitiveRenderer();
}

