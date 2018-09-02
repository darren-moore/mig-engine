#pragma once
#include "System.h"
#include "Components.h"
#include "Locator.h"
#include "collisionUtils.h"

class MovementSystem : public System {
public:
	void init() {
		addRequiredComponent<Player>();
		addRequiredComponent<gTransform>();
		addRequiredComponent<CollisionShape>();
		ioEngine_ = Locator::getIOEngine();
	}

private:
	IOEngine* ioEngine_;

	void execute(std::vector<Entity*>& entities, const float dt) {
		for (auto& e : entities) {
			Player* player = e->getComponent<Player>();
			gTransform* transform = e->getComponent<gTransform>();
			CollisionShape* collisionShape = e->getComponent<CollisionShape>();
			if (collisionShape->shape == CollisionShape::Shape::circle) { continue; }

			if (ioEngine_->isDown(player->upKey) &&
				transform->position.y() + collisionShape->offset.y() - collisionShape->scale.y() / 2 > 0) {
				transform->position[1] = transform->position[1] - player->speed;
			}
			if (ioEngine_->isDown(player->downKey) &&
				transform->position.y() + collisionShape->offset.y() + collisionShape->scale.y() / 2 < ioEngine_->getWindowHeight()) {
				transform->position[1] = transform->position[1] + player->speed;
			}
		}
	}
};

class SpriteRenderSystem : public System {
public:
	void init() {
		addRequiredComponent<Sprite>();
		addRequiredComponent<gTransform>();
		renderEngine_ = Locator::getRenderEngine();
		ioEngine_ = Locator::getIOEngine();
	}
private:
	RenderEngine* renderEngine_;
	IOEngine* ioEngine_;

	void execute(std::vector<Entity*>& entities, const float dt) {
		for (auto& e : entities) {
			renderEngine_->drawTexture(e->getComponent<Sprite>()->texture, e->getComponent<gTransform>()->position, Eigen::Vector2f(100, 100), ioEngine_->getCurrentWindowTime() * 2);
		}
	}
};

class QuadRenderSystem : public System {
public:
	void init() {
		addRequiredComponent<Quad>();
		addRequiredComponent<gTransform>();
		renderEngine_ = Locator::getRenderEngine();
		ioEngine_ = Locator::getIOEngine();
	}
private:
	RenderEngine* renderEngine_;
	IOEngine* ioEngine_;

	void execute(std::vector<Entity*>& entities, const float dt) {
		for (auto& e : entities) {
			Eigen::Vector2f offset = e->getComponent<Quad>()->offset;
			Eigen::Vector2f scale = e->getComponent<Quad>()->scale;
			Eigen::Vector2f position = e->getComponent<gTransform>()->position;
			renderEngine_->drawRectangle(offset.x() + position.x() - scale.x() / 2, offset.y() + position.y() - scale.y() / 2,
				offset.x() + position.x() + scale.x() / 2, offset.y() + position.y() + scale.y() / 2);
		}
	}
};

class CircleRenderSystem : public System {
public:
	void init() {
		addRequiredComponent<Circle>();
		addRequiredComponent<gTransform>();
		renderEngine_ = Locator::getRenderEngine();
		ioEngine_ = Locator::getIOEngine();
	}
private:
	RenderEngine* renderEngine_;
	IOEngine* ioEngine_;

	void execute(std::vector<Entity*>& entities, const float dt) {
		for (auto& e : entities) {
			Eigen::Vector2f offset = e->getComponent<Circle>()->offset;
			float radius = e->getComponent<Circle>()->radius;
			Eigen::Vector2f position = e->getComponent<gTransform>()->position;
			renderEngine_->drawCircle(offset.x() + position.x(), offset.y() + position.y(), radius);
		}
	}
};

class TimeIntegrationSystem : public System {
public:
	void init() {
		addRequiredComponent<Velocity>();
		addRequiredComponent<gTransform>();
	}
private:
	void execute(std::vector<Entity*>& entities, const float dt) {
		for (auto& e : entities) {
			e->getComponent<gTransform>()->position += dt * e->getComponent<Velocity>()->velocity;
		}
	}
};

class BallCollisionSystem : public System {
public:
	void init() {
		addRequiredComponent<gTransform>();
		addRequiredComponent<CollisionShape>();
		ioEngine_ = Locator::getIOEngine();
	}
private:
	IOEngine* ioEngine_;
	void execute(std::vector<Entity*>& entities, const float dt) {
		// Wall collisions
		float w = (float)ioEngine_->getWindowWidth();
		float h = (float)ioEngine_->getWindowHeight();
		for (auto& ball : entities) {
			if (ball->getComponent<CollisionShape>()->shape == CollisionShape::Shape::box) { continue; }
			Player* player = ball->getComponent<Player>();
			gTransform* transform = ball->getComponent<gTransform>();
			CollisionShape* collisionShape = ball->getComponent<CollisionShape>();
			Velocity* velocity = ball->getComponent<Velocity>();
			for (auto& e : entities) {
				if (e->getComponent<CollisionShape>()->shape == CollisionShape::Shape::circle) { continue; }
				if (circleRectangleCollision(e->getComponent<gTransform>()->position - e->getComponent<CollisionShape>()->scale/2, e->getComponent<gTransform>()->position + e->getComponent<CollisionShape>()->scale/2, transform->position, collisionShape->radius)) {
					velocity->velocity.x() *= -1;
					velocity->velocity.y() += transform->position.y() - e->getComponent<gTransform>()->position.y();
				}
			}

			// Wall collisions
			if (circleLineSegmentCollision(Eigen::Vector2f(0, 0), Eigen::Vector2f(w, 0), transform->position, collisionShape->radius)) {		// top
				velocity->velocity.y() *= -1;
				transform->position.y() = collisionShape->radius;
			}

			else if (circleLineSegmentCollision(Eigen::Vector2f(0, h), Eigen::Vector2f(w, h), transform->position, collisionShape->radius)) {	// bottom
				velocity->velocity.y() *= -1;
				transform->position.y() = h - collisionShape->radius;
			}

			else if (circleLineSegmentCollision(Eigen::Vector2f(0, 0), Eigen::Vector2f(0, h), transform->position, collisionShape->radius)) {	// left
				velocity->velocity.x() *= -1;
				transform->position.x() = collisionShape->radius;
			}

			else if (circleLineSegmentCollision(Eigen::Vector2f(w, 0), Eigen::Vector2f(w, h), transform->position, collisionShape->radius)) {	// right
				velocity->velocity.x() *= -1;
				transform->position.x() = w - collisionShape->radius;
			}
		}
	}
};
