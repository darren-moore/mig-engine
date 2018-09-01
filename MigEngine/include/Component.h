#pragma once
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

class Component {
public:
	Component() {};

	// This virtual function is required for Run-time type information(RTTI).
	// It allows typeis() to differentiate derived classes.
	virtual ~Component() {}

	static const int MAX_COMPONENTS = 32;
	bool active = true;

	static int getComponentType(Component* component) {
		return getComponentType(typeid(*component));
	}

	static int getComponentType(const std::type_info& type) {
		if (typeToIndex_.count(type) == 0) {
			std::type_index myIdx = type;
			typeToIndex_[type] = topIndex_;
			return topIndex_++;
		}
		else {
			return typeToIndex_[type];
		}
	}

private:
	static std::unordered_map<std::type_index, int> typeToIndex_;
	static int topIndex_;
};
