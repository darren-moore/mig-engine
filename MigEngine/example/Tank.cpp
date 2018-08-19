#include "Tank.h"

Tank::Tank() {
	Shader* shad = new Shader("src/vertShader.vert", "src/fragShader.frag");
	this->spriteRenderer = new SpriteRenderer(*shad);
	this->transform.position = Eigen::Vector2f(100, 100);
	this->transform.scale = Eigen::Vector2f(100, 100);
	Locator::getIOEngine().bindInput("UP", GLFW_KEY_W);
	Locator::getIOEngine().bindInput("DOWN", GLFW_KEY_S);
	Locator::getIOEngine().bindInput("LEFT", GLFW_KEY_A);
	Locator::getIOEngine().bindInput("RIGHT", GLFW_KEY_D);
}

Tank::~Tank() {
	delete spriteRenderer;
	Locator::getIOEngine().unbindInput("UP");
	Locator::getIOEngine().unbindInput("DOWN");
	Locator::getIOEngine().unbindInput("LEFT");
	Locator::getIOEngine().unbindInput("RIGHT");
}

void Tank::update(float const dt) {
	if (Locator::getIOEngine().isDown("UP")) {
		transform.position[1] = transform.position[1] - speed;
	}
	if (Locator::getIOEngine().isDown("DOWN")) {
		transform.position[1] = transform.position[1] + speed;
	}
	if (Locator::getIOEngine().isDown("LEFT")) {
		transform.position[0] = transform.position[0] - speed;
	}
	if (Locator::getIOEngine().isDown("RIGHT")) {
		transform.position[0] = transform.position[0] + speed;
	}

}

