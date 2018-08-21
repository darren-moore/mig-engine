#include "Renderer.h"

Renderer::Renderer() {
	shader_ = Locator::getResourceEngine()->getShader("defaultSpriteShader");
	renderEngine_ = Locator::getRenderEngine();
}

Renderer::Renderer(Shader* shader) : shader_(shader) {
	renderEngine_ = Locator::getRenderEngine();
};