#pragma once

#include "Component.h"
#include "Components.h"
#include <bitset>
#include <vector>

class Entity {
public:
	virtual ~Entity() {
		for (auto& component : components_) {
			delete component;
		}
	}

	void addComponent(Component* c) {
		int id = Component::getComponentType(c);
		components_[id] = c;
		componentSetSignature_[id] = 1;
	}

	template <typename T>
	T* getComponent() { return (T*) components_[Component::getComponentType(typeid(T))];}

	std::bitset<Component::MAX_COMPONENTS> getComponentSetSignature() { return componentSetSignature_; }

	bool active = true;

private:
	Component* components_[Component::MAX_COMPONENTS];
	std::bitset<Component::MAX_COMPONENTS> componentSetSignature_;
};
