#include "LAutils.h"
#include <math.h>

Eigen::Matrix4f eTranslate(const Eigen::Matrix4f& M, const Eigen::Vector3f& v) {
	Eigen::Matrix4f result(M);
	result.col(3) += v(0)*M.col(0) + v(1)*M.col(1) + v(2)*M.col(2);
	return result;
}

Eigen::Matrix4f eScale(const Eigen::Matrix4f& M, const Eigen::Vector3f& v) {
	Eigen::Matrix4f result(M);
	result.col(0) *= v(0);
	result.col(1) *= v(1);
	result.col(2) *= v(2);
	return result;
}


// Right handed, with -1,1 clip space. Adapted from glm's orthographic projection function.
Eigen::Matrix4f eOrtho(float left, float right, float bottom, float top, float zNear, float zFar) {
	Eigen::Matrix4f result = Eigen::Matrix4f::Identity();
	result(0, 0) = 2.0f / (right - left);
	result(1, 1) = 2.0f / (top - bottom);
	result(2, 2) = -2.0f / (zFar - zNear);
	result(0, 3) = -(right + left) / (right - left);
	result(1, 3) = -(top + bottom) / (top - bottom);
	result(2, 3) = -(zFar + zNear) / (zFar - zNear);
	return result;
}

Eigen::Matrix4f eRotate(const Eigen::Matrix4f& M, const float& theta, const Eigen::Vector3f& axis) {
	Eigen::Matrix4f rot;
	float c = cos(theta);
	float s = sin(theta);
	float omc = 1 - c; // "One Minus Cos"
	Eigen::Vector3f a = axis.normalized();
	Eigen::Matrix3f p = a * a.transpose();	// contains products of axis elements

	// From wikipedia
	rot <<
		c + p(0, 0)*omc, p(0, 1)*omc - a(2)*s, p(0, 2)*omc + a(1)*c, 0,
		p(1, 0)*omc + a(2)*s, c + p(1, 1)*omc, p(1, 2)*omc - a(0)*s, 0,
		p(2, 0)*omc - a(1)*s, p(2, 1)*omc + a(0)*s, c + p(2, 2)*omc, 0,
		0, 0, 0, 1;

	Eigen::Matrix4f result = M * rot;

	return result;
}
