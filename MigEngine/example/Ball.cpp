#include "Ball.h"
#include "collisionUtils.h"

using namespace Eigen;
Ball::Ball() {
	ioEngine_ = Locator::getIOEngine();
	primitiveRenderer = new PrimitiveRenderer();
}

void Ball::update(float const dt) {
	transform.position += dt * velocity_;
	detectResolveCollisions();
}

void Ball::draw() {
	primitiveRenderer->drawCircle(transform.position[0], transform.position[1], r_);
}

void Ball::detectResolveCollisions() {
	// Wall collisions
	float w = (float)ioEngine_->getWindowWidth();
	float h = (float)ioEngine_->getWindowHeight();

	// Wall collisions
	if (circleLineSegmentCollision(Vector2f(0, 0), Vector2f(w, 0), transform.position, r_)) {		// top
		velocity_.y() *= -1;
		transform.position.y() = r_;
	}
	else if (circleLineSegmentCollision(Vector2f(0, h), Vector2f(w, h), transform.position, r_)) {	// bottom
		velocity_.y() *= -1;
		transform.position.y() = h - r_;
	}
	else if (circleLineSegmentCollision(Vector2f(0, 0), Vector2f(0, h), transform.position, r_)) {	// left
		velocity_.x() *= -1;
		transform.position.x() = r_;
	}
	else if (circleLineSegmentCollision(Vector2f(w, 0), Vector2f(w, h), transform.position, r_)) {	// right
		velocity_.x() *= -1;
		transform.position.x() = w - r_;
	}

	if (circleRectangleCollision(p1->transform.position, p1->transform.position + Vector2f(30, 90), transform.position, r_)) {
		velocity_.x() *= -1;
	}
	else if (circleRectangleCollision(p2->transform.position, p2->transform.position + Vector2f(30, 90), transform.position, r_)) {
		velocity_.x() *= -1;
	}

}