#include "Paddle.h"

Paddle::Paddle() {
	primitiveRenderer = new PrimitiveRenderer();
	ioEngine_ = Locator::getIOEngine();
}

void Paddle::update(float const dt) {
	if (ioEngine_->isDown(paddleUp)) {
		transform.position[1] -= dt*speed;
	}
	if (ioEngine_->isDown(paddleDown)) {
		transform.position[1] += dt*speed;
	}
}

void Paddle::draw() {
	primitiveRenderer->drawRectangle(transform.position[0], transform.position[1], transform.position[0] + 10, transform.position[1] + 50);
}

