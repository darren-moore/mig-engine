#include "Ball.h"

Ball::Ball() {
	ioEngine_ = Locator::getIOEngine();
	primitiveRenderer = new PrimitiveRenderer();
}

void Ball::update(float const dt) {
	transform.position += dt*velocity_;
}

void Ball::draw() {
	primitiveRenderer->drawCircle(transform.position[0], transform.position[1], 20);
}