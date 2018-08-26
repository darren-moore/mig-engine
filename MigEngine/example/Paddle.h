#pragma once
#include "GameObject.h"
#include "IOEngine.h"

class Paddle : public GameObject {
public:
	Paddle();
	void update(float const dt);
	void draw();
	float speed = 150;
	std::string paddleUp;
	std::string paddleDown;
private:
	IOEngine* ioEngine_;

};
