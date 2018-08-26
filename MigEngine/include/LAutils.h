#pragma once
#include <Eigen/Core>
#include <math.h>

Eigen::Matrix4f eTranslate(const Eigen::Matrix4f& M, const Eigen::Vector3f& v);
Eigen::Matrix4f eScale(const Eigen::Matrix4f& M, const Eigen::Vector3f& v);
Eigen::Matrix4f eOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
Eigen::Matrix4f eRotate(const Eigen::Matrix4f& M, const float& theta, const Eigen::Vector3f& axis);