#pragma once

#include "Component.h"
#include "Texture.h"
#include <Eigen/Core>

struct Player : public Component {
	Player(std::string upKey, std::string downKey, float speed) :
		upKey(upKey), downKey(downKey), speed(speed) {};
	std::string upKey, downKey;
	float speed;
};

struct Velocity : public Component {
	Velocity(Eigen::Vector2f velocity) :
		velocity(velocity) {};
	Eigen::Vector2f velocity;
};

class Sprite : public Component {
public:
	Sprite(Texture* texture, Eigen::Vector2f origin = Eigen::Vector2f::Zero()) : texture(texture), origin(origin) {};
	Texture* texture;
	Eigen::Vector2f origin;
};

struct Quad : public Component {
	Quad(Eigen::Vector2f offset, Eigen::Vector2f scale) :
		offset(offset), scale(scale) {};
	Eigen::Vector2f offset, scale;
};

struct Circ : public Component {
	Circ(Eigen::Vector2f offset, float radius) :
		offset(offset), radius(radius) {};
	Eigen::Vector2f offset;
	float radius;
};