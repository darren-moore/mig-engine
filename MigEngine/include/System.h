#pragma once
#include "Component.h"
#include "Entity.h"
#include <set>

// Maybe have a "Component set ID" that hashes the set of components and does a comparison there...

class System {
public:
	std::set<Component> requiredComponents;
	virtual void init() {}
	virtual void execute(Entity& entity) = 0;
};
