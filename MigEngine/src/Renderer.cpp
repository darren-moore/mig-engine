#include "Renderer.h"

Renderer::Renderer() {
	renderEngine_ = Locator::getRenderEngine();
}

Renderer::Renderer(Shader* shader) : shader_(shader) {
	renderEngine_ = Locator::getRenderEngine();
};