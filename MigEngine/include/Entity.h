#pragma once

#include "Component.h"
#include "Components.h"


class Entity {
public:
	bool active = true;
	unsigned int id;

	gTransform* transform;
	Sprite* sprite;
	Player* player;

	Entity() {
		transform = NULL;
		sprite = NULL;
		player = NULL;
	}
	~Entity() {
		delete transform;
		delete sprite;
		delete player;
	}
};
