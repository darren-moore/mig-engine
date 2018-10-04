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
	void addCollisionEntity(std::shared_ptr<Entity> e);
	std::vector<std::shared_ptr<Entity>> getCollisions(std::shared_ptr<Entity> e);

private:
	std::unordered_map<std::shared_ptr<Entity>, std::vector<std::shared_ptr<Entity>>> entityToHitEntities;
	bool checkCollision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);
	
};