#pragma once
#include "System.h"
#include "Components.h"
#include "Locator.h"

class MovementSystem : public System {
public:
	void init() {
		addRequiredComponent<Player>();
		addRequiredComponent<gTransform>();
	}

private:
	void execute(Entity& e) {
		if (Locator::getIOEngine()->isDown(e.getComponent<Player>()->upKey)) {
			e.getComponent<gTransform>()->position[1] = e.getComponent<gTransform>()->position[1] - e.getComponent<Player>()->speed;
		}
		if (Locator::getIOEngine()->isDown(e.getComponent<Player>()->downKey)) {
			e.getComponent<gTransform>()->position[1] = e.getComponent<gTransform>()->position[1] + e.getComponent<Player>()->speed;
		}
		if (Locator::getIOEngine()->isDown(e.getComponent<Player>()->leftKey)) {
			e.getComponent<gTransform>()->position[0] = e.getComponent<gTransform>()->position[0] - e.getComponent<Player>()->speed;
		}
		if (Locator::getIOEngine()->isDown(e.getComponent<Player>()->rightKey)) {
			e.getComponent<gTransform>()->position[0] = e.getComponent<gTransform>()->position[0] + e.getComponent<Player>()->speed;
		}
	}
};

class DrawSystem : public System {
public:
	void init() {
		addRequiredComponent<Sprite>();
		addRequiredComponent<gTransform>();
	}
private:
	void execute(Entity& e) {
		Locator::getRenderEngine()->drawTexture(e.getComponent<Sprite>()->texture, e.getComponent<gTransform>()->position, Eigen::Vector2f(100, 100), Locator::getIOEngine()->getCurrentWindowTime() * 2);
	}
};