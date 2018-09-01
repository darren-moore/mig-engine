#pragma once
#include <type_traits>

#define MAX_COMPONENTS 32

class Component {
public:
	// Template provides a distinct copy of typeID for each component.
	template <typename T>
	static int getComponentTypeID() {
		static int typeID = initialiseComponentTypeID<T>(); // This line runs once for each typename provided. 
		return typeID;
	}

private:
	static int topIndex_;	// initialized to 0

	// Runtime type information is cached in getComponentTypeID.
	// Returns -1 for non-Component objects.
	template <typename T>
	static int initialiseComponentTypeID() {
		if (std::is_base_of<Component, T>::value)
			return topIndex_++;
		else
			return -1;
	}
};
