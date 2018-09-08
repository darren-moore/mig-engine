#pragma once

#include "Component.h"
#include "Shape.h"
#include "Texture.h"
#include <Eigen/Core>

struct CollisionShape : public Component {
	CollisionShape(Shape* shape) : 
		shape(shape) { };
	Shape* shape;
};

struct gTransform : public Component {
	gTransform(Eigen::Vector2f position = Eigen::Vector2f::Zero(), float rotation = 0, Eigen::Vector2f scale = Eigen::Vector2f::Ones()) :
		position(position), rotation(rotation), scale(scale) {};
	Eigen::Vector2f position;
	float rotation;	// in radians
	Eigen::Vector2f scale;
};
