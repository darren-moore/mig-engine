#pragma once
#include "System.h"
#include "Components.h"
#include "Locator.h"

class MovementSystem : public System {
public:
	void init() {
		addRequiredComponent<Player>();
		addRequiredComponent<gTransform>();
		ioEngine_ = Locator::getIOEngine();
	}

private:
	IOEngine* ioEngine_;

	void execute(Entity& e) {
		Player* player = e.getComponent<Player>();
		gTransform* transform = e.getComponent<gTransform>();

		if (ioEngine_->isDown(player->upKey)) {
			transform->position[1] = transform->position[1] - player->speed;
		}
		if (ioEngine_->isDown(e.getComponent<Player>()->downKey)) {
			transform->position[1] = transform->position[1] + player->speed;
		}
	}
};

class DrawSystem : public System {
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

	void execute(Entity& e) {
		renderEngine_->drawTexture(e.getComponent<Sprite>()->texture, e.getComponent<gTransform>()->position, Eigen::Vector2f(100, 100), ioEngine_->getCurrentWindowTime() * 2);
	}
};