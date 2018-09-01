#pragma once
#include "Component.h"
#include "Entity.h"
#include <bitset>

class System {
public:
	virtual void init() = 0;
	void validateAndExecute(Entity& e) { if (validateEntity(e)) execute(e);  }

protected:
	virtual void execute(Entity& e) = 0;

	bool validateEntity(Entity& e) { 
		return((e.getComponentSetSignature() & systemSignature_) == systemSignature_); 
	}

	template <typename T>
	void addRequiredComponent() {
		systemSignature_[Component::getComponentType(typeid(T))] = 1;
	}

private:
	std::bitset<Component::MAX_COMPONENTS> systemSignature_;
};
