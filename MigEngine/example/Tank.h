#pragma once

#include "GameObject.h"
#include "IOEngine.h"
#include "ResourceEngine.h"
#include "Shader.h"
#include <string>

class Tank : public GameObject {
public:
	Tank();
	~Tank();
	void update(float const dt);
	float speed = .5;
private:
	IOEngine* ioEngine_;
	ResourceEngine resourceEngine_;
};