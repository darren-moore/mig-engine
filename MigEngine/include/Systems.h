#pragma once
#include "System.h"
#include "Locator.h"

class MovementSystem : public System {
public:
	void execute(Entity& e) {
		if (e.player != NULL && e.transform != NULL) {
			if (Locator::getIOEngine()->isDown(e.player->upKey)) {
				e.transform->position[1] = e.transform->position[1] - e.player->speed;
			}
			if (Locator::getIOEngine()->isDown(e.player->downKey)) {
				e.transform->position[1] = e.transform->position[1] + e.player->speed;
			}
			if (Locator::getIOEngine()->isDown(e.player->leftKey)) {
				e.transform->position[0] = e.transform->position[0] - e.player->speed;
			}
			if (Locator::getIOEngine()->isDown(e.player->rightKey)) {
				e.transform->position[0] = e.transform->position[0] + e.player->speed;
			}
		}
	}
};

class DrawSystem : public System {
public:
	void execute(Entity& e) {
		if (e.sprite != NULL && e.transform != NULL) {
			Locator::getRenderEngine()->drawTexture(e.sprite->texture, e.transform->position, Eigen::Vector2f(100, 100), Locator::getIOEngine()->getCurrentWindowTime() * 2);
		}
	}
};