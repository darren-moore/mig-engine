#include "Tank.h"

Tank::Tank() {
	
	spriteRenderer = new SpriteRenderer();
	Locator::getResourceEngine()->addTexture("src/face.png", "face");
	spriteRenderer->setTexture(Locator::getResourceEngine()->getTexture("face"));
	transform.position = Eigen::Vector2f(100, 100);
	transform.scale = Eigen::Vector2f(100, 100);

	ioEngine_ = Locator::getIOEngine();
	ioEngine_->bindInput("UP", GLFW_KEY_W);
	ioEngine_->bindInput("DOWN", GLFW_KEY_S);
	ioEngine_->bindInput("LEFT", GLFW_KEY_A);
	ioEngine_->bindInput("RIGHT", GLFW_KEY_D);
}

Tank::~Tank() {
	delete spriteRenderer;
	ioEngine_->unbindInput("UP");
	ioEngine_->unbindInput("DOWN");
	ioEngine_->unbindInput("LEFT");
	ioEngine_->unbindInput("RIGHT");
}

void Tank::update(float const dt) {
	if (ioEngine_->isDown("UP")) {
		transform.position[1] = transform.position[1] - speed;
	}
	if (ioEngine_->isDown("DOWN")) {
		transform.position[1] = transform.position[1] + speed;
	}
	if (ioEngine_->isDown("LEFT")) {
		transform.position[0] = transform.position[0] - speed;
	}
	if (ioEngine_->isDown("RIGHT")) {
		transform.position[0] = transform.position[0] + speed;
	}
}


