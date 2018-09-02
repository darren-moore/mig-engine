#pragma once
#include <type_traits>
#include <exception>

#define MAX_COMPONENTS 32

struct NotComponentException : public std::exception {
};

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
	template <typename T>
	static int initialiseComponentTypeID() {
		if (std::is_base_of<Component, T>::value)
			return topIndex_++;
		else
			throw NotComponentException();
	}
};
