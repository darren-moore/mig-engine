#pragma once
#include "GameObject.h"

class Ball : public GameObject {
public:
	Ball();
	void setVelocity(Eigen::Vector2f velocity) { velocity_ = velocity; };
	void update(float const dt);
	void draw();
private:
	Eigen::Vector2f velocity_;
	IOEngine* ioEngine_;
	RenderEngine* renderEngine_;

};