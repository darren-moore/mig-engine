#pragma once

#include <Eigen/Core>

class gTransform {
public:
	Eigen::Vector2f position = Eigen::Vector2f::Zero();
	float rotation = 0;				// Rotation in radians
	Eigen::Vector2f scale = Eigen::Vector2f::Ones();
};
