#pragma once

#include <vector>
#include <unordered_map>
#include "Entity.h"
#include "StandardComponents.h"

class CollisionEngine {
public:

	CollisionEngine() {}
	~CollisionEngine() {}

	void init() {};
	void stop() {};

	void processCollisions();
	void addCollisionEntity(Entity* e);
	std::vector<Entity*> getCollisions(Entity* e);

private:
	std::unordered_map<Entity*, std::vector<Entity*>> entityToHitEntities;
	bool checkCollision(Entity* e1, Entity* e2);
	
};