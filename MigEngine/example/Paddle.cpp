#include "Paddle.h"

//Paddle::Paddle(float width, float height) : width(width), height(height) {
//	primitiveRenderer = new PrimitiveRenderer();
//	boxCollider = new BoxCollider();
//	boxCollider->scale = Eigen::Vector2f(width, height);
//	ioEngine_ = Locator::getIOEngine();
//}
//
//void Paddle::update(float const dt) {
//	if (ioEngine_->isDown(paddleUp)) {
//		transform.position[1] -= dt*speed;
//	}
//	if (ioEngine_->isDown(paddleDown)) {
//		transform.position[1] += dt*speed;
//	}
//}
//
//void Paddle::draw() {
//	primitiveRenderer->drawRectangle(transform.position[0] - width/2, transform.position[1] - height/2, transform.position[0] + width/2, transform.position[1] + height/2);
//}
//
