#pragma once
#include "Component.h"
#include "Entity.h"
#include <bitset>
#include <vector>

class System {
public:
	virtual void init() = 0;
	void validateAndExecute(std::vector<Entity*> entities, const float dt) {
		std::vector<Entity*> validatedEntities;
		for (auto& e : entities) {
			if (validateEntity(e))
				validatedEntities.push_back(e);
		}
		execute(validatedEntities, dt);
	}

protected:
	virtual void execute(std::vector<Entity*>& e, const float dt) = 0;

	bool validateEntity(Entity* e) { 
		return((e->getComponentSetSignature() & systemSignature_) == systemSignature_); 
	}

	template <typename T>
	void addRequiredComponent() {
		systemSignature_[Component::getComponentTypeID<T>()] = 1;
	}

private:
	std::bitset<MAX_COMPONENTS> systemSignature_;
};
