#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Eigen/Dense>

#include "Locator.h"
#include "IOEngine.h"
#include "Transform.h"
#include "Texture.h"
#include "PrimitiveRenderer.h"
#include "BoxCollider.h"
#include <vector>


class GameObject {
public:
	gTransform transform;
	bool active = true;
	std::vector<Component> components;

	Texture* texture;
	PrimitiveRenderer* primitiveRenderer;
	BoxCollider* boxCollider;

	GameObject(Eigen::Vector2f position = Eigen::Vector2f::Zero()) {
		texture = NULL;
		primitiveRenderer = NULL;
		boxCollider = NULL;
	}
	~GameObject() {
		delete texture;
		delete primitiveRenderer;
		delete boxCollider;
	}

	virtual void update(float const dt) {};
	virtual void draw() {};
};
