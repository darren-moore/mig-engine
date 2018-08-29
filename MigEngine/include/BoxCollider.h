#pragma once
#include "Component.h"
#include <Eigen/Dense>

class BoxCollider : public Component {
public:
	Eigen::Vector2f offset = Eigen::Vector2f::Zero();
	Eigen::Vector2f scale = Eigen::Vector2f::Ones();
	Eigen::Vector2f getTopLeft(Eigen::Vector2f position);
	Eigen::Vector2f getBottomRight(Eigen::Vector2f position);
};