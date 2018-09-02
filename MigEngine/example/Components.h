#pragma once
#include "Component.h"
#include "Texture.h"
#include <Eigen/Core>

// Should follow RAII, so these components should never need destructors...

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

struct gTransform : public Component {
	gTransform(Eigen::Vector2f position = Eigen::Vector2f::Zero(), float rotation = 0, Eigen::Vector2f scale = Eigen::Vector2f::Ones()) : 
		position(position), rotation(rotation), scale(scale) {};
	Eigen::Vector2f position;
	float rotation;	// in radians
	Eigen::Vector2f scale;
};

struct Player : public Component {
	Player(std::string upKey, std::string downKey, float speed) :
		upKey(upKey), downKey(downKey), speed(speed) {};
	std::string upKey, downKey;
	float speed;
};

struct BoxCollider : public Component {
	BoxCollider(Eigen::Vector2f offset, Eigen::Vector2f scale) :
		offset(offset), scale(scale) {};
	Eigen::Vector2f offset, scale;
};

struct CircleCollider : public Component {
	CircleCollider(Eigen::Vector2f offset, float radius) :
		offset(offset), radius(radius) {};
	Eigen::Vector2f offset;
	float radius;
};

struct Velocity : public Component {
	Velocity(Eigen::Vector2f velocity) :
		velocity(velocity) {};
	Eigen::Vector2f velocity;
};