#pragma once
#include "GameObject.h"
#include "Shader.h"

class Tank : public GameObject {
public:
	Tank();
	~Tank();
	void update(float const dt);
	float speed = .5;
};