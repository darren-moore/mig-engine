#pragma once

#include <Eigen/Core>

class Shape {
public:
	enum type {
		line, box, circle
	};
	Shape::type getType() { return shape; };
protected:
	Shape() {};
	Shape::type shape;
};

struct Line : public Shape {
	Line(Eigen::Vector2f a, Eigen::Vector2f b) : a(a), b(b) { shape = Shape::type::line; };
	Eigen::Vector2f a, b;
};

struct Box : public Shape {
	Box(Eigen::Vector2f offset, Eigen::Vector2f scale) : offset(offset), scale(scale) { shape = Shape::type::box; };
	Eigen::Vector2f offset, scale;
};

struct Circle : public Shape {
	Circle(Eigen::Vector2f offset, float r) : offset(offset), r(r) { shape = Shape::type::circle; };
	Eigen::Vector2f offset;
	float r;
};