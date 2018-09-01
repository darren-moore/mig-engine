#pragma once

#include "Component.h"
#include <bitset>
#include <vector>

class Entity {
public:
	virtual ~Entity() {
		for (auto& component : components_) {
			delete component;
		}
	}

	template <typename T>
	void applyComponent(T* c) {
		int id = Component::getComponentTypeID<T>();

		if (components_[id] != NULL) {
			delete components_[id];
		}
		components_[id] = c;
		componentSetSignature_[id] = 1;
	}

	template <typename T>
	T* getComponent() { return (T*) components_[Component::getComponentTypeID<T>()];}

	std::bitset<MAX_COMPONENTS> getComponentSetSignature() { return componentSetSignature_; }

	bool active = true;

private:
	Component* components_[MAX_COMPONENTS];
	std::bitset<MAX_COMPONENTS> componentSetSignature_;
};
