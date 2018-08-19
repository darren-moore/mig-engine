#include "Tank.h"

Tank::Tank() {
	Shader* shad = new Shader("src/vertShader.vert", "src/fragShader.frag");
	this->spriteRenderer = new SpriteRenderer(*shad);
	this->transform.position = Eigen::Vector2f(100, 100);
	this->transform.scale = Eigen::Vector2f(100, 100);
	// create audio component here. then in update when you play it, a signal is sent to the audioEngine.
	// OR: idea. Have a ComponentManager that stores lists of components to avoid observer pattern.
}

Tank::~Tank() {
	delete spriteRenderer;
}

