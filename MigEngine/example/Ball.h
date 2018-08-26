#pragma once
#include "GameObject.h"
#include "Paddle.h"

class Ball : public GameObject {
public:
	Ball();
	void setVelocity(Eigen::Vector2f velocity) { velocity_ = velocity; };
	void update(float const dt);
	void draw();
	Paddle* p1;
	Paddle* p2;
private:
	float r_ = 20;
	void detectResolveCollisions();
	Eigen::Vector2f velocity_;
	IOEngine* ioEngine_;
	RenderEngine* renderEngine_;

};