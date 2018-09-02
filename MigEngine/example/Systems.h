#pragma once
#include "System.h"
#include "Components.h"
#include "Locator.h"

class MovementSystem : public System {
public:
	void init() {
		addRequiredComponent<Player>();
		addRequiredComponent<gTransform>();
		addRequiredComponent<BoxCollider>();
		ioEngine_ = Locator::getIOEngine();
	}

private:
	IOEngine* ioEngine_;

	void execute(Entity& e, const float dt) {
		Player* player = e.getComponent<Player>();
		gTransform* transform = e.getComponent<gTransform>();
		BoxCollider* boxCollider = e.getComponent<BoxCollider>();

		if (ioEngine_->isDown(player->upKey) && 
			transform->position.y() + boxCollider->offset.y() - boxCollider->scale.y()/2 > 0) {
			transform->position[1] = transform->position[1] - player->speed;
		}
		if (ioEngine_->isDown(player->downKey) &&
			transform->position.y() + boxCollider->offset.y() + boxCollider->scale.y()/2 < ioEngine_->getWindowHeight()) {
			transform->position[1] = transform->position[1] + player->speed;
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

	void execute(Entity& e, const float dt) {
		renderEngine_->drawTexture(e.getComponent<Sprite>()->texture, e.getComponent<gTransform>()->position, Eigen::Vector2f(100, 100), ioEngine_->getCurrentWindowTime() * 2);
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

	void execute(Entity& e, const float dt) {
		Eigen::Vector2f offset = e.getComponent<Quad>()->offset;
		Eigen::Vector2f scale = e.getComponent<Quad>()->scale;
		Eigen::Vector2f position = e.getComponent<gTransform>()->position;
		renderEngine_->drawRectangle(offset.x() + position.x() - scale.x()/2, offset.y() + position.y() - scale.y() / 2,
			offset.x() + position.x() + scale.x()/2, offset.y() + position.y() + scale.y()/2);
	}
};

class TimeIntegrationSystem : public System {
public:
	void init() {
		addRequiredComponent<Velocity>();
		addRequiredComponent<gTransform>();
	}
private:
	void execute(Entity& e, const float dt) {
		e.getComponent<gTransform>()->position += dt * e.getComponent<Velocity>()->velocity;
	}
};

//class BallCollisionSystem : public System {
//public:
//	void init() {
//		addRequiredComponent<Velocity>();
//		addRequiredComponent<gTransform>();
//		addRequiredComponent<CircleCollider>();
//	}
//private:
//	void execute(Entity& e, const float dt) {
//
//		e.getComponent<gTransform>()->position += dt * e.getComponent<Velocity>()->velocity;
//	}
//};
