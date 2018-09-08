#pragma once
#include "Component.h"
#include "Entity.h"
#include <bitset>
#include <vector>

class System {
public:
	virtual void init() = 0;
	void validateAndExecute(Entity* e, const float dt) {
		if(validateEntity(e))
			execute(e, dt);
	}

protected:
	virtual void execute(Entity* e, const float dt) = 0;

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
