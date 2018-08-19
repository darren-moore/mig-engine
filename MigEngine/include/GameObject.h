#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Eigen/Dense>

#include "Transform.h"
#include "SpriteRenderer.h"


class GameObject {
public:
	Transform transform;
	bool active;

	SpriteRenderer* spriteRenderer;

	GameObject(Eigen::Vector2f position = Eigen::Vector2f::Zero()) {
		spriteRenderer = NULL;
	}
	~GameObject() {
		delete spriteRenderer;
	}

	virtual void update(float const dt) {};
	// Drawing is always done. Change the shader if you want to fix that...
};
