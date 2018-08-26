#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Eigen/Core>

#include "Locator.h"
#include "IOEngine.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "PrimitiveRenderer.h"


class GameObject {
public:
	gTransform transform;
	bool active = true;

	SpriteRenderer* spriteRenderer;
	PrimitiveRenderer* primitiveRenderer;

	GameObject(Eigen::Vector2f position = Eigen::Vector2f::Zero()) {
		spriteRenderer = NULL;
		primitiveRenderer = NULL;
	}
	~GameObject() {
		delete spriteRenderer;
		delete primitiveRenderer;
	}

	virtual void update(float const dt) {};
	virtual void draw() {};
};
