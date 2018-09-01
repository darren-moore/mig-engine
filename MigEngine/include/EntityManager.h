#pragma once
#include "Entity.h"
#include <vector>

class EntityManager {
public:
	Entity* createEntity();	// creates and adds to vector.
	void addComponent(Entity* e, Component* c); // Should be able to add all data on component creation.

private:
	std::vector<Entity*> entities;


};