#pragma once
#include <Eigen/Core>
#include <math.h>

bool circleLineSegmentCollision(const Eigen::Vector2f& p1, const Eigen::Vector2f& p2, const Eigen::Vector2f& c, float r);
bool circleRectangleCollision(const Eigen::Vector2f& b1, const Eigen::Vector2f& b2, const Eigen::Vector2f& c, float r);

