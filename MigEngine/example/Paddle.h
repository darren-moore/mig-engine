#pragma once
#include "GameObject.h"
#include "IOEngine.h"

class Paddle : public GameObject {
public:
	Paddle(float width, float height);
	void update(float const dt);
	void draw();
	float speed = 150;
	float width;
	float height;
	std::string paddleUp;
	std::string paddleDown;
private:
	IOEngine* ioEngine_;
};
